#include "FPGA_5G.h"
#include "IConnection.h"
#include "Logger.h"
#include "LMS64CProtocol.h"
#include <ciso646>
#include <vector>
#include <map>
#include <math.h>
#include <iostream>

namespace lime
{

FPGA_5G::FPGA_5G(uint32_t slaveID, uint32_t lmsSlaveId) : FPGA(slaveID, lmsSlaveId) {}

int FPGA_5G::SetInterfaceFreq(double txRate_Hz, double rxRate_Hz, double txPhase, double rxPhase, int channel)
{
    lime::FPGA::FPGA_PLL_clock clocks[2];

    std::cerr<< "FPGA_5G" << std::endl;
    printf("Phases : tx phase %f rx phase %f \n", txPhase, rxPhase);

    clocks[0].index = 0;
    clocks[0].outFrequency = rxRate_Hz;
    clocks[1].index = 1;
    clocks[1].outFrequency = rxRate_Hz;
    clocks[1].phaseShift_deg = rxPhase;
     if (FPGA_5G::SetPllFrequency(1, rxRate_Hz, clocks, 2)!=0)
        return -1;

    clocks[0].index = 0;
    clocks[0].outFrequency = txRate_Hz;
    clocks[1].index = 1;
    clocks[1].outFrequency = txRate_Hz;
    clocks[1].phaseShift_deg = txPhase;
    if (FPGA_5G::SetPllFrequency(0, txRate_Hz, clocks, 2)!=0)  //B.J.
        return -1;

    return 0;
}

int FPGA_5G::SetPllFrequency(const uint8_t pllIndex, const double inputFreq, FPGA_PLL_clock* clocks, const uint8_t clockCount)
{
    //Xilinx boards have different phase control mechanism
    double phase = clocks[1].phaseShift_deg;
    WriteRegister(0x0020, phase);
    return FPGA::SetPllFrequency(pllIndex, inputFreq, clocks, clockCount);
}

int FPGA_5G::SetInterfaceFreq(double txRate_Hz, double rxRate_Hz, int channel)
{
    if(channel == 1 || channel == 2)
        return 0;
    return FPGA::SetInterfaceFreq(txRate_Hz, rxRate_Hz, channel);
}

} //namespace lime