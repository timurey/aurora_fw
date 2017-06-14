#ifndef HTTPD_H_
#define HTTPD_H_

#include "error.h"

error_t httpdConfigure (void);
error_t httpdStart(void);
#endif /* HTTPD_H_ */
