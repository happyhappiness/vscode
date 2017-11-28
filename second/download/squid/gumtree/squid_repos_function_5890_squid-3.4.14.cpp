static void
netdbFreeNameEntry(void *data)
{
    net_db_name *x = (net_db_name *)data;
    xfree(x->hash.key);
    memFree(x, MEM_NET_DB_NAME);
}