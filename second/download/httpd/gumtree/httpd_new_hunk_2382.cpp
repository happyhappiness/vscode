 * @param r the current request
 * @return The number of bytes sent
 */
AP_DECLARE(int) ap_rputc(int c, request_rec *r);

/**
 * Write a buffer for the current request
 * @param buf The buffer to write
 * @param nbyte The number of bytes to send from the buffer
 * @param r The current request
 * @return The number of bytes sent
 */
AP_DECLARE(int) ap_rwrite(const void *buf, int nbyte, request_rec *r);

/**
 * Output a string for the current request
 * @param str The string to output
 * @param r The current request
 * @return The number of bytes sent
 * @note ap_rputs may be implemented as macro or inline function
 */
static APR_INLINE int ap_rputs(const char *str, request_rec *r)
{
    return ap_rwrite(str, strlen(str), r);
}

/**
 * Write an unspecified number of strings to the request
 * @param r The current request
 * @param ... The strings to write
 * @return The number of bytes sent
 */
AP_DECLARE_NONSTD(int) ap_rvputs(request_rec *r,...)
                       AP_FN_ATTR_SENTINEL;

/**
 * Output data to the client in a printf format
 * @param r The current request
 * @param fmt The format string
 * @param vlist The arguments to use to fill out the format string
