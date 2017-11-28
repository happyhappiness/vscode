const char *
httpMakeVaryMark(HttpRequest * request, HttpReply const * reply)
{
    String vary, hdr;
    const char *pos = NULL;
    const char *item;
    const char *value;
    int ilen;
    static String vstr;

    vstr.clean();
    vary = reply->header.getList(HDR_VARY);

    while (strListGetItem(&vary, ',', &item, &ilen, &pos)) {
        char *name = (char *)xmalloc(ilen + 1);
        xstrncpy(name, item, ilen + 1);
        Tolower(name);

        if (strcmp(name, "*") == 0) {
            /* Can not handle "Vary: *" withtout ETag support */
            safe_free(name);
            vstr.clean();
            break;
        }

        strListAdd(&vstr, name, ',');
        hdr = request->header.getByName(name);
        safe_free(name);
        value = hdr.termedBuf();

        if (value) {
            value = rfc1738_escape_part(value);
            vstr.append("=\"", 2);
            vstr.append(value);
            vstr.append("\"", 1);
        }

        hdr.clean();
    }

    vary.clean();
#if X_ACCELERATOR_VARY

    pos = NULL;
    vary = reply->header.getList(HDR_X_ACCELERATOR_VARY);

    while (strListGetItem(&vary, ',', &item, &ilen, &pos)) {
        char *name = (char *)xmalloc(ilen + 1);
        xstrncpy(name, item, ilen + 1);
        Tolower(name);
        strListAdd(&vstr, name, ',');
        hdr = request->header.getByName(name);
        safe_free(name);
        value = hdr.termedBuf();

        if (value) {
            value = rfc1738_escape_part(value);
            vstr.append("=\"", 2);
            vstr.append(value);
            vstr.append("\"", 1);
        }

        hdr.clean();
    }

    vary.clean();
#endif

    debugs(11, 3, "httpMakeVaryMark: " << vstr);
    return vstr.termedBuf();
}