
#define DAV_DO_COPY		0
#define DAV_DO_MOVE		1


#if 1
#define DAV_DEBUG        1
#define DEBUG_CR         "\n"
#define DBG0(f)          ap_log_error(APLOG_MARK, \
				APLOG_ERR, 0, NULL, (f))
#define DBG1(f,a1)       ap_log_error(APLOG_MARK, \
				APLOG_ERR, 0, NULL, f, a1)
#define DBG2(f,a1,a2)    ap_log_error(APLOG_MARK, \
				APLOG_ERR, 0, NULL, f, a1, a2)
#define DBG3(f,a1,a2,a3) ap_log_error(APLOG_MARK, \
                                APLOG_ERR, 0, NULL, f, a1, a2, a3)
#else
#undef DAV_DEBUG
#define DEBUG_CR	""
#endif

#define DAV_INFINITY    INT_MAX    /* for the Depth: header */

/* Create a set of DAV_DECLARE(type), DAV_DECLARE_NONSTD(type) and 
 * DAV_DECLARE_DATA with appropriate export and import tags for the platform
 */
#if !defined(WIN32)
#define DAV_DECLARE(type)            type
