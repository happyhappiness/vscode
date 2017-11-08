static int TestOptionalFn(const char *szStr)
{
    ap_log_error(APLOG_MARK,APLOG_ERR,OK,NULL, APLOGNO(01871)
                 "Optional function test said: %s",szStr);

    return OK;
}