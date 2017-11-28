static void
netdbExchangeDone(void *data)
{
    netdbExchangeState *ex = (netdbExchangeState *)data;
    debugs(38, 3, "netdbExchangeDone: " << ex->e->url()  );
    HTTPMSGUNLOCK(ex->r);
    storeUnregister(ex->sc, ex->e, ex);
    ex->e->unlock();
    cbdataReferenceDone(ex->p);
    cbdataFree(ex);
}