
#include "os_port.h"
#include "xprintf.h"
#define TRACE_LEVEL 4
#define TRACE_PRINTF(...) osSuspendAllTasks(), xprintf(__VA_ARGS__), osResumeAllTasks()
#include "debug.h"

#define LOG_INFO(...) TRACE_INFO(__VA_ARGS__)

#define LOG_STATUS(x)  do {if (x) \
  {\
    TRACE_INFO(""PRIfgRed"FAILED"PRIfgDefault". Error number: %u\r\n", x);\
  }\
  else\
  {\
    TRACE_INFO(""PRIfgGreen"success\r\n"PRIfgDefault"");\
  }\
} while (0)
/* End of file with last new-line */