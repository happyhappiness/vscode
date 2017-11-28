static void
clientdbFreeItem(void *data)
{
    ClientInfo *c = (ClientInfo *)data;
    delete c;
}