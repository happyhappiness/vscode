static int win32_pre_config(apr_pool_t *pconf_, apr_pool_t *plog, apr_pool_t *ptemp)
{
    win_nt = (osver.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS);
    return OK;
}