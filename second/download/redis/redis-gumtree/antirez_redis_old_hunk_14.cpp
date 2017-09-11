
/* This is the low level function implementing both:
 *
 *  RM_Log()
 *  RM_LogIOError()
 *
 */
void RM_LogRaw(RedisModule *module, const char *levelstr, const char *fmt, va_list ap) {
