static int TestOptionalFn(const char *szStr)
{
    ap_log_error(APLOG_MARK,APLOG_ERR,OK,NULL,
                 "Optional function test said: %s",szStr);

    return OK;
}