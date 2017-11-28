bool
shm_portable_segment_name_is_path()
{
#if _SQUID_HPUX_ || _SQUID_OSF_ || defined(__vms) || (_SQUID_FREEBSD_ && (__FreeBSD__ < 7))
    return true;
#elif _SQUID_FREEBSD_
    int jailed = 0;
    size_t len = sizeof(jailed);
    ::sysctlbyname("security.jail.jailed", &jailed, &len, NULL, 0);
    return !jailed;
#else
    return false;
#endif
}