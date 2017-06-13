//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// Do not include on semihosting and when freestanding
#if !defined(OS_USE_SEMIHOSTING) && !(__STDC_HOSTED__ == 0)

// ----------------------------------------------------------------------------

#include <errno.h>
#include <unistd.h>
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
//#include "diag/Trace.h"
extern USBD_HandleTypeDef hUsbDeviceFS;
// ----------------------------------------------------------------------------
#define RxBufferSize 64

char RxBuffer[RxBufferSize];
volatile uint readIndex = RxBufferSize;
volatile uint RxFifoIndex = 0;
// When using retargetted configurations, the standard write() system call,
// after a long way inside newlib, finally calls this implementation function.

// Based on the file descriptor, it can send arrays of characters to
// different physical devices.

// Currently only the output and error file descriptors are tested,
// and the characters are forwarded to the trace device, mainly
// for demonstration purposes. Adjust it for your specific needs.

// For freestanding applications this file is not used and can be safely
// ignored.

ssize_t _write(int fd, const char *buf, size_t nbyte);
int _read(int fd, char *instring, uint count);
uint8_t USB_Receive_FS (uint8_t* Buf, uint32_t *Len);

ssize_t _write(int fd, const char *buf, size_t nbyte)
{
  ssize_t len = -1;
  uint32_t timeout;
  switch (fd)
  {
  case STDOUT_FILENO: /*stdout*/

  case STDERR_FILENO:                       /* stderr */
    timeout = HAL_GetTick() + 500; // 0.5 second timeout
    while (HAL_GetTick() < timeout)
    {
      if (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED)
      {
        continue; //We can wait...
      }
      int result = CDC_Transmit_FS((uint8_t *) buf, nbyte);
      if (result == USBD_OK)
      {
        len = nbyte; //result is ok/
        break;
      }
      if (result == USBD_BUSY)
      {
        continue; //USB is busy. We can wait...
      }
      if (result == USBD_FAIL)
      {
        break; //Error.
      }
      // save some power!
      //  __WFI();
    }
    break;
  default:
    errno = EBADF;
    return -1;
  }
  return len;
}

/*
 * the _read() routine returns any characters that have been placed into
 * the RxBuffer by the USB receive FIFO process which emulates the UART
 * DMA circular buffer
 *
 * The UART receiver is set up with DMA in circular buffer mode.  This means that
 * it will continue receiving characters forever regardless of whether any are
 * taken out.  It will just write over the previous buffer if it overflows
 *
 * To know whether there are any characters in the buffer we look at the counter
 * register in the DMA channel assigned to the UART Rx buffer.  This count starts
 * at the size of the transfer and is decremented after a transfer to memory is done.
 *
 * We maintain a mirror DMA count register value readIndex.  If they are the same no data is
 * available.  If they are different, the DMA has decremented its counter
 * so we transfer data until they are the same or the rx buffer is full.  We
 * wrap our down counter the same way the DMA does in circular mode.
 */

int _read(int fd, char *instring, uint count){
     uint32_t bytesread = 0;

     if(count > bytesread){
          while(readIndex == (RxBufferSize - RxFifoIndex)){}
          {
               while((count > bytesread) & (readIndex !=(RxBufferSize - RxFifoIndex ))){
                    instring[bytesread] = RxBuffer[RxBufferSize - readIndex];
                    if(readIndex == (0))
                         readIndex = RxBufferSize;
                    else readIndex--;
                    bytesread++;
               }
          }
     }
     return (int)bytesread;
}

/*
 * This routine is called by CDC_Receive_FS() which is a callback
 * from the underlying USB Device servicing code which gets called
 * when there is data received on the USB endpoint for the device.
 * This routine therefore acts like a circular buffer DMA for data
 * received on the USB port similar to the behavior of the circulat
 * buffer implemented on the UART receive DMA when a UART is used
 * for console I/O
 */

uint8_t USB_Receive_FS (uint8_t* Buf, uint32_t *Len)
{
     volatile uint32_t counter = 0;

     while(counter < *Len){
          RxBuffer[RxFifoIndex ] = Buf[counter];
          counter++, RxFifoIndex++;
          if(RxFifoIndex  == RxBufferSize)
               RxFifoIndex  = 0;
          }

  return (USBD_OK);
}

// ----------------------------------------------------------------------------

#endif // !defined(OS_USE_SEMIHOSTING) && !(__STDC_HOSTED__ == 0)
