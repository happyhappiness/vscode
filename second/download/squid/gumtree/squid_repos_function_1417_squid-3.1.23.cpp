static void
mainRotate(void)
{
    icmpEngine.Close();
#if USE_DNSSERVERS
    dnsShutdown();
#endif
    redirectShutdown();
    authenticateShutdown();
    externalAclShutdown();

    _db_rotate_log();		/* cache.log */
    storeDirWriteCleanLogs(1);
    storeLogRotate();		/* store.log */
    accessLogRotate();		/* access.log */
    useragentRotateLog();	/* useragent.log */
    refererRotateLog();		/* referer.log */
#if ICAP_CLIENT
    icapLogRotate();               /*icap.log*/
#endif
#if WIP_FWD_LOG
    fwdLogRotate();
#endif

    icmpEngine.Open();
#if USE_DNSSERVERS
    dnsInit();
#endif
    redirectInit();
    authenticateInit(&Config.authConfiguration);
    externalAclInit();
}