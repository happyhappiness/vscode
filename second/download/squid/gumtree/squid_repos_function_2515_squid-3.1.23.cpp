void
FtpStateData::parseListing()
{
    char *buf = data.readBuf->content();
    char *sbuf;			/* NULL-terminated copy of termedBuf */
    char *end;
    char *line;
    char *s;
    char *t;
    size_t linelen;
    size_t usable;
    StoreEntry *e = entry;
    size_t len = data.readBuf->contentSize();

    if (!len) {
        debugs(9, 3, HERE << "no content to parse for " << e->url()  );
        return;
    }

    /*
     * We need a NULL-terminated buffer for scanning, ick
     */
    sbuf = (char *)xmalloc(len + 1);
    xstrncpy(sbuf, buf, len + 1);
    end = sbuf + len - 1;

    while (*end != '\r' && *end != '\n' && end > sbuf)
        end--;

    usable = end - sbuf;

    debugs(9, 3, HERE << "usable = " << usable);

    if (usable == 0) {
        debugs(9, 3, HERE << "didn't find end for " << e->url()  );
        xfree(sbuf);
        return;
    }

    debugs(9, 3, HERE << (unsigned long int)len << " bytes to play with");

    line = (char *)memAllocate(MEM_4K_BUF);
    end++;
    e->buffer();	/* released when done processing current data payload */
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

        assert(t != NULL);

        writeReplyBody(t, strlen(t));
    }

    data.readBuf->consume(usable);
    memFree(line, MEM_4K_BUF);
    xfree(sbuf);
}