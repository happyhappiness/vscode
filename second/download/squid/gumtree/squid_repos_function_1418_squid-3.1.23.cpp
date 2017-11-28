static void
setEffectiveUser(void)
{
    keepCapabilities();
    leave_suid();		/* Run as non privilegied user */
#ifdef _SQUID_OS2_

    return;
#endif

    if (geteuid() == 0) {
        debugs(0, 0, "Squid is not safe to run as root!  If you must");
        debugs(0, 0, "start Squid as root, then you must configure");
        debugs(0, 0, "it to run as a non-priveledged user with the");
        debugs(0, 0, "'cache_effective_user' option in the config file.");
        fatal("Don't run Squid as root, set 'cache_effective_user'!");
    }
}