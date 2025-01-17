#ifndef LIME_LMS64C_LMS7002M_OVER_USB_H
#define LIME_LMS64C_LMS7002M_OVER_USB_H

#include "comms/IComms.h"
#include "USB_CSR_Pipe.h"
#include <memory>

namespace lime {

/** @brief A class for communicating with a device's ADF4002 chip over a USB interface. */
class LMS64C_ADF4002_Over_USB : public IComms
{
  public:
    LMS64C_ADF4002_Over_USB(std::shared_ptr<USB_CSR_Pipe> dataPort);

    OpStatus SPI(const uint32_t* MOSI, uint32_t* MISO, uint32_t count) override;
    OpStatus SPI(uint32_t spiBusAddress, const uint32_t* MOSI, uint32_t* MISO, uint32_t count) override;

  private:
    std::shared_ptr<USB_CSR_Pipe> pipe;
};

} // namespace lime

#endif // LIME_LMS64C_LMS7002M_OVER_USB_H
