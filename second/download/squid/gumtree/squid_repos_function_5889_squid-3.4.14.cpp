static void
netdbFreeNetdbEntry(void *data)
{
    netdbEntry *n = (netdbEntry *)data;
    safe_free(n->peers);
    memFree(n, MEM_NETDBENTRY);
}