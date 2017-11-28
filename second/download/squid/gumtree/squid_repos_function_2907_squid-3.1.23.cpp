static void
clientdbFreeItem(void *data)
{
    ClientInfo *c = (ClientInfo *)data;
    safe_free(c->hash.key);
    memFree(c, MEM_CLIENT_INFO);
}