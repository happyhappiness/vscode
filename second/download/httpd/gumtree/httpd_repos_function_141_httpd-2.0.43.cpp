static int ImportOptionalHookTestHook(const char *szStr)
{
    ap_log_error(APLOG_MARK,APLOG_ERR,OK,NULL,"Optional hook test said: %s",
		 szStr);

    return OK;
}