static int log_log_id(const ap_errorlog_info *info, const char *arg,
                      char *buf, int buflen)
{
    /*
     * C: log conn log_id if available,
     * c: log conn log id if available and not a once-per-request log line
     * else: log request log id if available
     */
    if (arg && !strcasecmp(arg, "c")) {
        if (info->c && (*arg != 'C' || !info->r)) {
            return cpystrn(buf, info->c->log_id, buflen);
        }
    }
    else if (info->rmain) {
        return cpystrn(buf, info->rmain->log_id, buflen);
    }
    return 0;
}