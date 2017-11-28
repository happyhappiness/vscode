static void
whoisClose(int fd, void *data)
{
    WhoisState *p = (WhoisState *)data;
    debugs(75, 3, "whoisClose: FD " << fd);
    p->entry->unlock();
    cbdataFree(p);
}