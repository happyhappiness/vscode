void esi_startElementSAXFunc(void * ctx, const xmlChar * name, const xmlChar ** atts)
{
    int count=0;
    xmlChar **tmp = (xmlChar **)atts;

    while (tmp && *tmp != NULL) {
        count++;
        tmp++;
    }

    // we increased on every key and value
    count /= 2;

    ESILibxml2Parser *p = (ESILibxml2Parser *)ctx;

    p->getClient()->start((const char *)name, (const char **)atts, count);
}