void esi_endElementSAXFunc(void * ctx, const xmlChar * name)
{
    ESILibxml2Parser *p = (ESILibxml2Parser *)ctx;
    p->getClient()->end((const char *)name);
}