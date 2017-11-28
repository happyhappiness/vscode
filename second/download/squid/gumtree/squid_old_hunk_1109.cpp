    header.clean();
    return result;
}

/* test if a field is present */
int
HttpHeader::has(http_hdr_type id) const
{
    assert_eid(id);
    assert(id != HDR_OTHER);
    debugs(55, 9, this << " lookup for " << id);
    return CBIT_TEST(mask, id);
}

void
HttpHeader::putInt(http_hdr_type id, int number)
{
    assert_eid(id);
    assert(Headers[id].type == ftInt);  /* must be of an appropriate type */
    assert(number >= 0);
    addEntry(new HttpHeaderEntry(id, NULL, xitoa(number)));
}

void
HttpHeader::putInt64(http_hdr_type id, int64_t number)
{
    assert_eid(id);
    assert(Headers[id].type == ftInt64);    /* must be of an appropriate type */
    assert(number >= 0);
    addEntry(new HttpHeaderEntry(id, NULL, xint64toa(number)));
}

void
HttpHeader::putTime(http_hdr_type id, time_t htime)
{
    assert_eid(id);
    assert(Headers[id].type == ftDate_1123);    /* must be of an appropriate type */
    assert(htime >= 0);
    addEntry(new HttpHeaderEntry(id, NULL, mkrfc1123(htime)));
}

void
HttpHeader::insertTime(http_hdr_type id, time_t htime)
{
    assert_eid(id);
    assert(Headers[id].type == ftDate_1123);    /* must be of an appropriate type */
    assert(htime >= 0);
    insertEntry(new HttpHeaderEntry(id, NULL, mkrfc1123(htime)));
}

void
HttpHeader::putStr(http_hdr_type id, const char *str)
{
    assert_eid(id);
    assert(Headers[id].type == ftStr);  /* must be of an appropriate type */
    assert(str);
    addEntry(new HttpHeaderEntry(id, NULL, str));
}

void
HttpHeader::putAuth(const char *auth_scheme, const char *realm)
{
    assert(auth_scheme && realm);
    httpHeaderPutStrf(this, HDR_WWW_AUTHENTICATE, "%s realm=\"%s\"", auth_scheme, realm);
}

void
HttpHeader::putCc(const HttpHdrCc * cc)
{
    MemBuf mb;
    Packer p;
    assert(cc);
    /* remove old directives if any */
    delById(HDR_CACHE_CONTROL);
    /* pack into mb */
    mb.init();
    packerToMemInit(&p, &mb);
    cc->packInto(&p);
    /* put */
    addEntry(new HttpHeaderEntry(HDR_CACHE_CONTROL, NULL, mb.buf));
    /* cleanup */
    packerClean(&p);
    mb.clean();
}

void
HttpHeader::putContRange(const HttpHdrContRange * cr)
{
    MemBuf mb;
    Packer p;
    assert(cr);
    /* remove old directives if any */
    delById(HDR_CONTENT_RANGE);
    /* pack into mb */
    mb.init();
    packerToMemInit(&p, &mb);
    httpHdrContRangePackInto(cr, &p);
    /* put */
    addEntry(new HttpHeaderEntry(HDR_CONTENT_RANGE, NULL, mb.buf));
    /* cleanup */
    packerClean(&p);
    mb.clean();
}

void
HttpHeader::putRange(const HttpHdrRange * range)
{
    MemBuf mb;
    Packer p;
    assert(range);
    /* remove old directives if any */
    delById(HDR_RANGE);
    /* pack into mb */
    mb.init();
    packerToMemInit(&p, &mb);
    range->packInto(&p);
    /* put */
    addEntry(new HttpHeaderEntry(HDR_RANGE, NULL, mb.buf));
    /* cleanup */
    packerClean(&p);
    mb.clean();
}

void
HttpHeader::putSc(HttpHdrSc *sc)
{
    MemBuf mb;
    Packer p;
    assert(sc);
    /* remove old directives if any */
    delById(HDR_SURROGATE_CONTROL);
    /* pack into mb */
    mb.init();
    packerToMemInit(&p, &mb);
    sc->packInto(&p);
    /* put */
    addEntry(new HttpHeaderEntry(HDR_SURROGATE_CONTROL, NULL, mb.buf));
    /* cleanup */
    packerClean(&p);
    mb.clean();
}

void
HttpHeader::putWarning(const int code, const char *const text)
{
    char buf[512];
    snprintf(buf, sizeof(buf), "%i %s \"%s\"", code, visible_appname_string, text);
    putStr(HDR_WARNING, buf);
}

/* add extension header (these fields are not parsed/analyzed/joined, etc.) */
void
HttpHeader::putExt(const char *name, const char *value)
{
    assert(name && value);
    debugs(55, 8, this << " adds ext entry " << name << " : " << value);
    addEntry(new HttpHeaderEntry(HDR_OTHER, name, value));
}

int
HttpHeader::getInt(http_hdr_type id) const
{
    assert_eid(id);
    assert(Headers[id].type == ftInt);  /* must be of an appropriate type */
    HttpHeaderEntry *e;

    if ((e = findEntry(id)))
        return e->getInt();

    return -1;
}

int64_t
HttpHeader::getInt64(http_hdr_type id) const
{
    assert_eid(id);
    assert(Headers[id].type == ftInt64);    /* must be of an appropriate type */
    HttpHeaderEntry *e;

    if ((e = findEntry(id)))
        return e->getInt64();

    return -1;
}

time_t
HttpHeader::getTime(http_hdr_type id) const
{
    HttpHeaderEntry *e;
    time_t value = -1;
    assert_eid(id);
    assert(Headers[id].type == ftDate_1123);    /* must be of an appropriate type */

    if ((e = findEntry(id))) {
        value = parse_rfc1123(e->value.termedBuf());
        httpHeaderNoteParsedEntry(e->id, e->value, value < 0);
    }

    return value;
}

/* sync with httpHeaderGetLastStr */
const char *
HttpHeader::getStr(http_hdr_type id) const
{
    HttpHeaderEntry *e;
    assert_eid(id);
    assert(Headers[id].type == ftStr);  /* must be of an appropriate type */

    if ((e = findEntry(id))) {
        httpHeaderNoteParsedEntry(e->id, e->value, 0);  /* no errors are possible */
        return e->value.termedBuf();
    }

    return NULL;
}

/* unusual */
const char *
HttpHeader::getLastStr(http_hdr_type id) const
{
    HttpHeaderEntry *e;
    assert_eid(id);
    assert(Headers[id].type == ftStr);  /* must be of an appropriate type */

    if ((e = findLastEntry(id))) {
        httpHeaderNoteParsedEntry(e->id, e->value, 0);  /* no errors are possible */
        return e->value.termedBuf();
    }

    return NULL;
}

HttpHdrCc *
HttpHeader::getCc() const
{
    if (!CBIT_TEST(mask, HDR_CACHE_CONTROL))
        return NULL;
    PROF_start(HttpHeader_getCc);

    String s;
    getList(HDR_CACHE_CONTROL, &s);

    HttpHdrCc *cc=new HttpHdrCc();

    if (!cc->parse(s)) {
        delete cc;
        cc = NULL;
