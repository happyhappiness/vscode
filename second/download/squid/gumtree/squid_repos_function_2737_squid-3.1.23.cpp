int
HttpHeader::parse(const char *header_start, const char *header_end)
{
    const char *field_ptr = header_start;
    HttpHeaderEntry *e, *e2;

    PROF_start(HttpHeaderParse);

    assert(header_start && header_end);
    debugs(55, 7, "parsing hdr: (" << this << ")" << std::endl << getStringPrefix(header_start, header_end));
    HttpHeaderStats[owner].parsedCount++;

    char *nulpos;
    if ((nulpos = (char*)memchr(header_start, '\0', header_end - header_start))) {
        debugs(55, 1, "WARNING: HTTP header contains NULL characters {" <<
               getStringPrefix(header_start, nulpos) << "}\nNULL\n{" << getStringPrefix(nulpos+1, header_end));
        goto reset;
    }

    /* common format headers are "<name>:[ws]<value>" lines delimited by <CRLF>.
     * continuation lines start with a (single) space or tab */
    while (field_ptr < header_end) {
        const char *field_start = field_ptr;
        const char *field_end;

        do {
            const char *this_line = field_ptr;
            field_ptr = (const char *)memchr(field_ptr, '\n', header_end - field_ptr);

            if (!field_ptr)
                goto reset;	/* missing <LF> */

            field_end = field_ptr;

            field_ptr++;	/* Move to next line */

            if (field_end > this_line && field_end[-1] == '\r') {
                field_end--;	/* Ignore CR LF */
                /* Ignore CR CR LF in relaxed mode */

                if (Config.onoff.relaxed_header_parser && field_end > this_line + 1 && field_end[-1] == '\r') {
                    debugs(55, Config.onoff.relaxed_header_parser <= 0 ? 1 : 2,
                           "WARNING: Double CR characters in HTTP header {" << getStringPrefix(field_start, field_end) << "}");
                    field_end--;
                }
            }

            /* Barf on stray CR characters */
            if (memchr(this_line, '\r', field_end - this_line)) {
                debugs(55, 1, "WARNING: suspicious CR characters in HTTP header {" <<
                       getStringPrefix(field_start, field_end) << "}");

                if (Config.onoff.relaxed_header_parser) {
                    char *p = (char *) this_line;	/* XXX Warning! This destroys original header content and violates specifications somewhat */

                    while ((p = (char *)memchr(p, '\r', field_end - p)) != NULL)
                        *p++ = ' ';
                } else
                    goto reset;
            }

            if (this_line + 1 == field_end && this_line > field_start) {
                debugs(55, 1, "WARNING: Blank continuation line in HTTP header {" <<
                       getStringPrefix(header_start, header_end) << "}");
                goto reset;
            }
        } while (field_ptr < header_end && (*field_ptr == ' ' || *field_ptr == '\t'));

        if (field_start == field_end) {
            if (field_ptr < header_end) {
                debugs(55, 1, "WARNING: unparseable HTTP header field near {" <<
                       getStringPrefix(field_start, header_end) << "}");
                goto reset;
            }

            break;		/* terminating blank line */
        }

        if ((e = HttpHeaderEntry::parse(field_start, field_end)) == NULL) {
            debugs(55, 1, "WARNING: unparseable HTTP header field {" <<
                   getStringPrefix(field_start, field_end) << "}");
            debugs(55, Config.onoff.relaxed_header_parser <= 0 ? 1 : 2,
                   " in {" << getStringPrefix(header_start, header_end) << "}");

            if (Config.onoff.relaxed_header_parser)
                continue;
            else
                goto reset;
        }

        if (e->id == HDR_CONTENT_LENGTH && (e2 = findEntry(e->id)) != NULL) {
//            if (e->value.cmp(e2->value.termedBuf()) != 0) {
            if (e->value != e2->value) {
                int64_t l1, l2;
                debugs(55, Config.onoff.relaxed_header_parser <= 0 ? 1 : 2,
                       "WARNING: found two conflicting content-length headers in {" << getStringPrefix(header_start, header_end) << "}");

                if (!Config.onoff.relaxed_header_parser) {
                    delete e;
                    goto reset;
                }

                if (!httpHeaderParseOffset(e->value.termedBuf(), &l1)) {
                    debugs(55, 1, "WARNING: Unparseable content-length '" << e->value << "'");
                    delete e;
                    continue;
                } else if (!httpHeaderParseOffset(e2->value.termedBuf(), &l2)) {
                    debugs(55, 1, "WARNING: Unparseable content-length '" << e2->value << "'");
                    delById(e2->id);
                } else if (l1 > l2) {
                    delById(e2->id);
                } else {
                    delete e;
                    continue;
                }
            } else {
                debugs(55, Config.onoff.relaxed_header_parser <= 0 ? 1 : 2,
                       "NOTICE: found double content-length header");

                if (Config.onoff.relaxed_header_parser) {
                    delete e;
                    continue;
                } else {
                    delete e;
                    goto reset;
                }
            }
        }

        if (e->id == HDR_OTHER && stringHasWhitespace(e->name.termedBuf())) {
            debugs(55, Config.onoff.relaxed_header_parser <= 0 ? 1 : 2,
                   "WARNING: found whitespace in HTTP header name {" <<
                   getStringPrefix(field_start, field_end) << "}");

            if (!Config.onoff.relaxed_header_parser) {
                delete e;
                goto reset;
            }
        }

        addEntry(e);
    }

    if (chunked()) {
        // RFC 2616 section 4.4: ignore Content-Length with Transfer-Encoding
        delById(HDR_CONTENT_LENGTH);
    }

    PROF_stop(HttpHeaderParse);
    return 1;			/* even if no fields where found, it is a valid header */
reset:
    PROF_stop(HttpHeaderParse);
    return reset();
}