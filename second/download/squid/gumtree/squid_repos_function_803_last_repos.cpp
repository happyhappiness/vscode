static void
free_refreshpattern(RefreshPattern ** head)
{
    delete *head;
    *head = nullptr;

#if USE_HTTP_VIOLATIONS
    refresh_nocache_hack = 0;

#endif
}