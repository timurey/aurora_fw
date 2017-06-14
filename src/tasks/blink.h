#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

osThreadId blinkTaskHandle;

void BlinkTask(void const * argument);