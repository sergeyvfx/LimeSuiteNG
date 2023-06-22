#ifdef __unix__
#include <unistd.h>
#endif

#include "LitePCIe.h"
#include "LimeSDR_X3.h"

#include <fstream>
#include <map>
#include <unistd.h>
#include <fcntl.h>

using namespace lime;

void __loadLimeSDR_X3(void) //TODO fixme replace with LoadLibrary/dlopen
{
    static LimeSDR_X3Entry limesdr_X3Support; // self register on initialization
}

LimeSDR_X3Entry::LimeSDR_X3Entry() : DeviceRegistryEntry("LimeSDR_X3")
{
}

LimeSDR_X3Entry::~LimeSDR_X3Entry()
{
}

std::vector<DeviceHandle> LimeSDR_X3Entry::enumerate(const DeviceHandle &hint)
{
    std::vector<DeviceHandle> handles;
    DeviceHandle handle;
    handle.media = "PCIe";

    const std::string searchDevName("LimeX3");
    const std::string pattern(searchDevName + "[0-9]*_control");
    const std::vector<std::string> devices = LitePCIe::GetDevicesWithPattern(pattern);

    for(const auto& port : devices)
    {
        size_t pos = port.find(searchDevName);
        if(pos == std::string::npos)
            continue;

        std::string dev_nr(&port[pos+searchDevName.length()], &port[port.find("_")]);
        handle.name = GetDeviceName(LMS_DEV_LIMESDR_X3) + (dev_nr == "0" ? "" : " (" + dev_nr + ")");

        handle.addr = port.substr(0, port.find("_"));
        handles.push_back(handle);
    }
    return handles;
}

SDRDevice* LimeSDR_X3Entry::make(const DeviceHandle &handle)
{
    LitePCIe* control = new LitePCIe();
    std::vector<LitePCIe*> txStreams(3);
    std::vector<LitePCIe*> rxStreams(3);
    try {
        std::string controlFile(handle.addr + "_control");
        control->Open(controlFile.c_str(), O_RDWR);

        std::string streamFile("");
        for (int i=0; i<3; ++i)
        {
            char portName[128];
            sprintf(portName, "%s_trx%i", handle.addr.c_str(), i);
            rxStreams[i] = new LitePCIe();
            rxStreams[i]->SetPathName(portName);

            sprintf(portName, "%s_write%i", handle.addr.c_str(), i);
            txStreams[i] = new LitePCIe();
            txStreams[i]->SetPathName(portName);
        }
        return new LimeSDR_X3(control, std::move(rxStreams), std::move(txStreams));
    }
    catch ( std::runtime_error &e )
    {
        delete control;
        char reason[256];
        sprintf(reason, "Unable to connect to device using handle(%s): %s", handle.serialize().c_str(), e.what());
        throw std::runtime_error(reason);
    }
}