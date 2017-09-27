#include "apr_strings.h"
#include "httpd.h"
#include "http_log.h"
#include "http_core.h"
#include "util_ebcdic.h"

/* we know core's module_index is 0 */
#undef APLOG_MODULE_INDEX
#define APLOG_MODULE_INDEX AP_CORE_MODULE_INDEX

apr_status_t ap_init_ebcdic(apr_pool_t *pool)
{
    apr_status_t rv;

    rv = apr_xlate_open(&ap_hdrs_to_ascii, "ISO-8859-1", APR_DEFAULT_CHARSET, pool);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL, APLOGNO(00040)
                     "apr_xlate_open() failed");
        return rv;
    }

    rv = apr_xlate_open(&ap_hdrs_from_ascii, APR_DEFAULT_CHARSET, "ISO-8859-1", pool);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL, APLOGNO(00041)
                     "apr_xlate_open() failed");
        return rv;
    }

    rv = apr_MD5InitEBCDIC(ap_hdrs_to_ascii);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL, APLOGNO(00042)
                     "apr_MD5InitEBCDIC() failed");
        return rv;
    }

    rv = apr_base64init_ebcdic(ap_hdrs_to_ascii, ap_hdrs_from_ascii);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL, APLOGNO(00043)
                     "apr_base64init_ebcdic() failed");
        return rv;
    }

    rv = apr_SHA1InitEBCDIC(ap_hdrs_to_ascii);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL, APLOGNO(00044)
                     "apr_SHA1InitEBCDIC() failed");
        return rv;
    }

    return APR_SUCCESS;
}
