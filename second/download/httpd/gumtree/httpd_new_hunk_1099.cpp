#include "http_main.h"
#include "http_request.h"

static int asis_handler(request_rec *r)
{
    FILE *f;
    const char *location;

    r->allowed |= (1 << M_GET);
    if (r->method_number != M_GET)
	return DECLINED;
    if (r->finfo.st_mode == 0) {
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
++ apache_1.3.1/src/modules/standard/mod_auth_anon.c	1998-07-04 06:08:49.000000000 +0800
