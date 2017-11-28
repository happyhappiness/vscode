static void
whoisClose(const CommCloseCbParams &params)
{
    WhoisState *p = (WhoisState *)params.data;
    debugs(75, 3, "whoisClose: FD " << params.fd);
    p->entry->unlock("whoisClose");
    delete p;
}