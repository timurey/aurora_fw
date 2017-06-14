#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

osThreadId networkTaskHandle;

void NetworkTask(void const * argument);