static void
netdbFreeNameEntry(void *data)
{
    net_db_name *x = (net_db_name *)data;
    delete x;
}