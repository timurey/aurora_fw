
#include "os_port.h"
#include "xprintf.h"
#define TRACE_LEVEL 4
#define TRACE_PRINTF(...) osSuspendAllTasks(), xprintf(__VA_ARGS__), osResumeAllTasks()
#include "debug.h"

#define LOG_INFO(...) TRACE_INFO(__VA_ARGS__)

#define LOG_STATUS(x)  do {if (x) \
  {\
    TRACE_INFO("\a"PRIfgRed"FAILED"PRIfgDefault". Error number: 0x%X at %s:%d \r\n", x, __FILE__, __LINE__);\
  }\
  else\
  {\
    TRACE_INFO(""PRIfgGreen"success\r\n"PRIfgDefault"");\
  }\
} while (0)

#define LOG_DUMP(...) put_dump(__VA_ARGS__)
/* End of file with last new-line */