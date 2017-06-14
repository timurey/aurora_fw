#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

osThreadId fatfsTaskHandle;

void FatFsTask(void const * argument);