static const char *
ssl_get_attribute(X509_NAME * name, const char *attribute_name)
{
    static char buffer[1024];
    int nid;

    buffer[0] = '\0';

    if (strcmp(attribute_name, "DN") == 0) {
        X509_NAME_oneline(name, buffer, sizeof(buffer));
        goto done;
    }

    nid = OBJ_txt2nid((char *) attribute_name);

    if (nid == 0) {
        debugs(83, DBG_IMPORTANT, "WARNING: Unknown SSL attribute name '" << attribute_name << "'");
        return NULL;
    }

    X509_NAME_get_text_by_NID(name, nid, buffer, sizeof(buffer));

done:
    return *buffer ? buffer : NULL;
}