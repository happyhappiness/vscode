int
storePendingNClients(const StoreEntry * e)
{
    MemObject *mem = e->mem_obj;
    int npend = NULL == mem ? 0 : mem->nclients;
    debugs(90, 3, "storePendingNClients: returning " << npend);
    return npend;
}