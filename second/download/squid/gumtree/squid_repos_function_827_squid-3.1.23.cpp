static void
whoisTimeout(int fd, void *data)
{
    WhoisState *p = (WhoisState *)data;
    debugs(75, 1, "whoisTimeout: " << p->entry->url()  );
    whoisClose(fd, p);
}