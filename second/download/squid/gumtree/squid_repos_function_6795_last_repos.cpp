xmlEntityPtr esi_getEntitySAXFunc(void * ctx,  const xmlChar * name)
{
    xmlEntityPtr res = xmlGetDocEntity(entity_doc, name);

    if (res == NULL) {
        const htmlEntityDesc *ent = htmlEntityLookup(name);

        if (ent != NULL) {
            char tmp[32];
            snprintf(tmp, 32, "&#%d;", ent->value);
            res = xmlAddDocEntity(entity_doc, (const xmlChar *)name, XML_INTERNAL_GENERAL_ENTITY, NULL, NULL, (const xmlChar *)tmp);
        }
    }

    return res;
}