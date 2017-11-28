void
Ftp::Gateway::parseListing()
{
    char *buf = data.readBuf->content();
    char *sbuf;         /* NULL-terminated copy of termedBuf */
    char *end;
    char *line;
    char *s;
    MemBuf *t;
    size_t linelen;
    size_t usable;
    size_t len = data.readBuf->contentSize();

    if (!len) {
        debugs(9, 3, HERE << "no content to parse for " << entry->url()  );
        return;
    }

    /*
     * We need a NULL-terminated buffer for scanning, ick
     */
    sbuf = (char *)xmalloc(len + 1);
    xstrncpy(sbuf, buf, len + 1);
    end = sbuf + len - 1;

    while (*end != '\r' && *end != '\n' && end > sbuf)
        --end;

    usable = end - sbuf;

    debugs(9, 3, HERE << "usable = " << usable << " of " << len << " bytes.");

    if (usable == 0) {
        if (buf[0] == '\0' && len == 1) {
            debugs(9, 3, HERE << "NIL ends data from " << entry->url() << " transfer problem?");
            data.readBuf->consume(len);
        } else {
            debugs(9, 3, HERE << "didn't find end for " << entry->url());
            debugs(9, 3, HERE << "buffer remains (" << len << " bytes) '" << rfc1738_do_escape(buf,0) << "'");
        }
        xfree(sbuf);
        return;
    }

    debugs(9, 3, HERE << (unsigned long int)len << " bytes to play with");

    line = (char *)memAllocate(MEM_4K_BUF);
    ++end;
    s = sbuf;
    s += strspn(s, crlf);

    for (; s < end; s += strcspn(s, crlf), s += strspn(s, crlf)) {
        debugs(9, 7, HERE << "s = {" << s << "}");
        linelen = strcspn(s, crlf) + 1;

        if (linelen < 2)
            break;

        if (linelen > 4096)
            linelen = 4096;

        xstrncpy(line, s, linelen);

        debugs(9, 7, HERE << "{" << line << "}");

        if (!strncmp(line, "total", 5))
            continue;

        t = htmlifyListEntry(line);

        if ( t != NULL) {
            debugs(9, 7, HERE << "listing append: t = {" << t->contentSize() << ", '" << t->content() << "'}");
            listing.append(t->content(), t->contentSize());
            delete t;
        }
    }

    debugs(9, 7, HERE << "Done.");
    data.readBuf->consume(usable);
    memFree(line, MEM_4K_BUF);
    xfree(sbuf);
}