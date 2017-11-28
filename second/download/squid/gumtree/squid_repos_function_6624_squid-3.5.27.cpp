void esi_charactersSAXFunc(void *ctx, const xmlChar *ch, int len)
{
    ESILibxml2Parser *p = (ESILibxml2Parser *)ctx;
    p->getClient()->parserDefault((const char *)ch, len);
}