     header.clean();
     return result;
 }
 
 /* test if a field is present */
 int
-HttpHeader::has(http_hdr_type id) const
+HttpHeader::has(Http::HdrType id) const
 {
-    assert_eid(id);
-    assert(id != HDR_OTHER);
+    assert(any_registered_header(id));
     debugs(55, 9, this << " lookup for " << id);
     return CBIT_TEST(mask, id);
 }
 
 void
-HttpHeader::putInt(http_hdr_type id, int number)
+HttpHeader::addVia(const AnyP::ProtocolVersion &ver, const HttpHeader *from)
 {
-    assert_eid(id);
-    assert(Headers[id].type == ftInt);  /* must be of an appropriate type */
-    assert(number >= 0);
-    addEntry(new HttpHeaderEntry(id, NULL, xitoa(number)));
+    // TODO: do not add Via header for messages where Squid itself
+    // generated the message (i.e., Downloader or ESI) there should be no Via header added at all.
+
+    if (Config.onoff.via) {
+        SBuf buf;
+        // RFC 7230 section 5.7.1.: protocol-name is omitted when
+        // the received protocol is HTTP.
+        if (ver.protocol > AnyP::PROTO_NONE && ver.protocol < AnyP::PROTO_UNKNOWN &&
+                ver.protocol != AnyP::PROTO_HTTP && ver.protocol != AnyP::PROTO_HTTPS)
+            buf.appendf("%s/", AnyP::ProtocolType_str[ver.protocol]);
+        buf.appendf("%d.%d %s", ver.major, ver.minor, ThisCache);
+        const HttpHeader *hdr = from ? from : this;
+        SBuf strVia = StringToSBuf(hdr->getList(Http::HdrType::VIA));
+        if (!strVia.isEmpty())
+            strVia.append(", ", 2);
+        strVia.append(buf);
+        // XXX: putStr() still suffers from String size limits
+        Must(strVia.length() < String::SizeMaxXXX());
+        delById(Http::HdrType::VIA);
+        putStr(Http::HdrType::VIA, strVia.c_str());
+    }
 }
 
 void
-HttpHeader::putInt64(http_hdr_type id, int64_t number)
+HttpHeader::putInt(Http::HdrType id, int number)
 {
-    assert_eid(id);
-    assert(Headers[id].type == ftInt64);    /* must be of an appropriate type */
+    assert(any_registered_header(id));
+    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftInt);  /* must be of an appropriate type */
     assert(number >= 0);
-    addEntry(new HttpHeaderEntry(id, NULL, xint64toa(number)));
+    addEntry(new HttpHeaderEntry(id, NULL, xitoa(number)));
 }
 
 void
-HttpHeader::putTime(http_hdr_type id, time_t htime)
+HttpHeader::putInt64(Http::HdrType id, int64_t number)
 {
-    assert_eid(id);
-    assert(Headers[id].type == ftDate_1123);    /* must be of an appropriate type */
-    assert(htime >= 0);
-    addEntry(new HttpHeaderEntry(id, NULL, mkrfc1123(htime)));
+    assert(any_registered_header(id));
+    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftInt64);    /* must be of an appropriate type */
+    assert(number >= 0);
+    addEntry(new HttpHeaderEntry(id, NULL, xint64toa(number)));
 }
 
 void
-HttpHeader::insertTime(http_hdr_type id, time_t htime)
+HttpHeader::putTime(Http::HdrType id, time_t htime)
 {
-    assert_eid(id);
-    assert(Headers[id].type == ftDate_1123);    /* must be of an appropriate type */
+    assert(any_registered_header(id));
+    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftDate_1123);    /* must be of an appropriate type */
     assert(htime >= 0);
-    insertEntry(new HttpHeaderEntry(id, NULL, mkrfc1123(htime)));
+    addEntry(new HttpHeaderEntry(id, NULL, mkrfc1123(htime)));
 }
 
 void
-HttpHeader::putStr(http_hdr_type id, const char *str)
+HttpHeader::putStr(Http::HdrType id, const char *str)
 {
-    assert_eid(id);
-    assert(Headers[id].type == ftStr);  /* must be of an appropriate type */
+    assert(any_registered_header(id));
+    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftStr);  /* must be of an appropriate type */
     assert(str);
     addEntry(new HttpHeaderEntry(id, NULL, str));
 }
 
 void
 HttpHeader::putAuth(const char *auth_scheme, const char *realm)
 {
     assert(auth_scheme && realm);
-    httpHeaderPutStrf(this, HDR_WWW_AUTHENTICATE, "%s realm=\"%s\"", auth_scheme, realm);
+    httpHeaderPutStrf(this, Http::HdrType::WWW_AUTHENTICATE, "%s realm=\"%s\"", auth_scheme, realm);
 }
 
 void
 HttpHeader::putCc(const HttpHdrCc * cc)
 {
-    MemBuf mb;
-    Packer p;
     assert(cc);
     /* remove old directives if any */
-    delById(HDR_CACHE_CONTROL);
+    delById(Http::HdrType::CACHE_CONTROL);
     /* pack into mb */
+    MemBuf mb;
     mb.init();
-    packerToMemInit(&p, &mb);
-    cc->packInto(&p);
+    cc->packInto(&mb);
     /* put */
-    addEntry(new HttpHeaderEntry(HDR_CACHE_CONTROL, NULL, mb.buf));
+    addEntry(new HttpHeaderEntry(Http::HdrType::CACHE_CONTROL, NULL, mb.buf));
     /* cleanup */
-    packerClean(&p);
     mb.clean();
 }
 
 void
 HttpHeader::putContRange(const HttpHdrContRange * cr)
 {
-    MemBuf mb;
-    Packer p;
     assert(cr);
     /* remove old directives if any */
-    delById(HDR_CONTENT_RANGE);
+    delById(Http::HdrType::CONTENT_RANGE);
     /* pack into mb */
+    MemBuf mb;
     mb.init();
-    packerToMemInit(&p, &mb);
-    httpHdrContRangePackInto(cr, &p);
+    httpHdrContRangePackInto(cr, &mb);
     /* put */
-    addEntry(new HttpHeaderEntry(HDR_CONTENT_RANGE, NULL, mb.buf));
+    addEntry(new HttpHeaderEntry(Http::HdrType::CONTENT_RANGE, NULL, mb.buf));
     /* cleanup */
-    packerClean(&p);
     mb.clean();
 }
 
 void
 HttpHeader::putRange(const HttpHdrRange * range)
 {
-    MemBuf mb;
-    Packer p;
     assert(range);
     /* remove old directives if any */
-    delById(HDR_RANGE);
+    delById(Http::HdrType::RANGE);
     /* pack into mb */
+    MemBuf mb;
     mb.init();
-    packerToMemInit(&p, &mb);
-    range->packInto(&p);
+    range->packInto(&mb);
     /* put */
-    addEntry(new HttpHeaderEntry(HDR_RANGE, NULL, mb.buf));
+    addEntry(new HttpHeaderEntry(Http::HdrType::RANGE, NULL, mb.buf));
     /* cleanup */
-    packerClean(&p);
     mb.clean();
 }
 
 void
 HttpHeader::putSc(HttpHdrSc *sc)
 {
-    MemBuf mb;
-    Packer p;
     assert(sc);
     /* remove old directives if any */
-    delById(HDR_SURROGATE_CONTROL);
+    delById(Http::HdrType::SURROGATE_CONTROL);
     /* pack into mb */
+    MemBuf mb;
     mb.init();
-    packerToMemInit(&p, &mb);
-    sc->packInto(&p);
+    sc->packInto(&mb);
     /* put */
-    addEntry(new HttpHeaderEntry(HDR_SURROGATE_CONTROL, NULL, mb.buf));
+    addEntry(new HttpHeaderEntry(Http::HdrType::SURROGATE_CONTROL, NULL, mb.buf));
     /* cleanup */
-    packerClean(&p);
     mb.clean();
 }
 
 void
 HttpHeader::putWarning(const int code, const char *const text)
 {
     char buf[512];
     snprintf(buf, sizeof(buf), "%i %s \"%s\"", code, visible_appname_string, text);
-    putStr(HDR_WARNING, buf);
+    putStr(Http::HdrType::WARNING, buf);
 }
 
 /* add extension header (these fields are not parsed/analyzed/joined, etc.) */
 void
 HttpHeader::putExt(const char *name, const char *value)
 {
     assert(name && value);
     debugs(55, 8, this << " adds ext entry " << name << " : " << value);
-    addEntry(new HttpHeaderEntry(HDR_OTHER, name, value));
+    addEntry(new HttpHeaderEntry(Http::HdrType::OTHER, name, value));
 }
 
 int
-HttpHeader::getInt(http_hdr_type id) const
+HttpHeader::getInt(Http::HdrType id) const
 {
-    assert_eid(id);
-    assert(Headers[id].type == ftInt);  /* must be of an appropriate type */
+    assert(any_registered_header(id));
+    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftInt);  /* must be of an appropriate type */
     HttpHeaderEntry *e;
 
     if ((e = findEntry(id)))
         return e->getInt();
 
     return -1;
 }
 
 int64_t
-HttpHeader::getInt64(http_hdr_type id) const
+HttpHeader::getInt64(Http::HdrType id) const
 {
-    assert_eid(id);
-    assert(Headers[id].type == ftInt64);    /* must be of an appropriate type */
+    assert(any_registered_header(id));
+    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftInt64);    /* must be of an appropriate type */
     HttpHeaderEntry *e;
 
     if ((e = findEntry(id)))
         return e->getInt64();
 
     return -1;
 }
 
 time_t
-HttpHeader::getTime(http_hdr_type id) const
+HttpHeader::getTime(Http::HdrType id) const
 {
     HttpHeaderEntry *e;
     time_t value = -1;
-    assert_eid(id);
-    assert(Headers[id].type == ftDate_1123);    /* must be of an appropriate type */
+    assert(any_registered_header(id));
+    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftDate_1123);    /* must be of an appropriate type */
 
     if ((e = findEntry(id))) {
         value = parse_rfc1123(e->value.termedBuf());
         httpHeaderNoteParsedEntry(e->id, e->value, value < 0);
     }
 
     return value;
 }
 
 /* sync with httpHeaderGetLastStr */
 const char *
-HttpHeader::getStr(http_hdr_type id) const
+HttpHeader::getStr(Http::HdrType id) const
 {
     HttpHeaderEntry *e;
-    assert_eid(id);
-    assert(Headers[id].type == ftStr);  /* must be of an appropriate type */
+    assert(any_registered_header(id));
+    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftStr);  /* must be of an appropriate type */
 
     if ((e = findEntry(id))) {
-        httpHeaderNoteParsedEntry(e->id, e->value, 0);  /* no errors are possible */
+        httpHeaderNoteParsedEntry(e->id, e->value, false);  /* no errors are possible */
         return e->value.termedBuf();
     }
 
     return NULL;
 }
 
 /* unusual */
 const char *
-HttpHeader::getLastStr(http_hdr_type id) const
+HttpHeader::getLastStr(Http::HdrType id) const
 {
     HttpHeaderEntry *e;
-    assert_eid(id);
-    assert(Headers[id].type == ftStr);  /* must be of an appropriate type */
+    assert(any_registered_header(id));
+    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftStr);  /* must be of an appropriate type */
 
     if ((e = findLastEntry(id))) {
-        httpHeaderNoteParsedEntry(e->id, e->value, 0);  /* no errors are possible */
+        httpHeaderNoteParsedEntry(e->id, e->value, false);  /* no errors are possible */
         return e->value.termedBuf();
     }
 
     return NULL;
 }
 
 HttpHdrCc *
 HttpHeader::getCc() const
 {
-    if (!CBIT_TEST(mask, HDR_CACHE_CONTROL))
+    if (!CBIT_TEST(mask, Http::HdrType::CACHE_CONTROL))
         return NULL;
     PROF_start(HttpHeader_getCc);
 
     String s;
-    getList(HDR_CACHE_CONTROL, &s);
+    getList(Http::HdrType::CACHE_CONTROL, &s);
 
     HttpHdrCc *cc=new HttpHdrCc();
 
     if (!cc->parse(s)) {
         delete cc;
         cc = NULL;
