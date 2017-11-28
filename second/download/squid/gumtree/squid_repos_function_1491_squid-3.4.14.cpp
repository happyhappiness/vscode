static void
mainRotate(void)
{
    icmpEngine.Close();
#if USE_DNSHELPER
    dnsShutdown();
#endif
    redirectShutdown();
#if USE_AUTH
    authenticateRotate();
#endif
    externalAclShutdown();

    _db_rotate_log();		/* cache.log */
    storeDirWriteCleanLogs(1);
    storeLogRotate();		/* store.log */
    accessLogRotate();		/* access.log */
#if ICAP_CLIENT
    icapLogRotate();               /*icap.log*/
#endif
    icmpEngine.Open();
#if USE_DNSHELPER
    dnsInit();
#endif
    redirectInit();
#if USE_AUTH
    authenticateInit(&Auth::TheConfig);
#endif
    externalAclInit();
}