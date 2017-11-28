void esi_commentSAXFunc(void * ctx, const xmlChar * value)
{
    ESILibxml2Parser *p = (ESILibxml2Parser *)ctx;
    p->getClient()->parserComment((const char *)value);
}