#ifndef FPGA_X3_H
#define FPGA_X3_H

#include "FPGA_common.h"

namespace lime
{

class FPGA_X3 : public FPGA
{
public:
    FPGA_X3(uint32_t slaveID, uint32_t lmsSlaveId);
    virtual ~FPGA_X3(){};
    int SetInterfaceFreq(double f_Tx_Hz, double f_Rx_Hz, double txPhase, double rxPhase, int ch = 0) override;
    int SetInterfaceFreq(double f_Tx_Hz, double f_Rx_Hz, int ch = 0) override;
    int SetPllFrequency(const uint8_t pllIndex, const double inputFreq, FPGA_PLL_clock* clocks, const uint8_t clockCount);
};

}
#endif // FPGA_Q_H