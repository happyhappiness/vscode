 
     /* Interface functions */
     void clean();
     void append(const HttpHeader * src);
     bool update(HttpHeader const *fresh);
     void compact();
-    int reset();
-    int parse(const char *header_start, const char *header_end);
-    void packInto(Packer * p, bool mask_sensitive_info=false) const;
+    int parse(const char *header_start, size_t len);
+    void packInto(Packable * p, bool mask_sensitive_info=false) const;
     HttpHeaderEntry *getEntry(HttpHeaderPos * pos) const;
-    HttpHeaderEntry *findEntry(http_hdr_type id) const;
+    HttpHeaderEntry *findEntry(Http::HdrType id) const;
     int delByName(const char *name);
-    int delById(http_hdr_type id);
+    int delById(Http::HdrType id);
     void delAt(HttpHeaderPos pos, int &headers_deleted);
     void refreshMask();
     void addEntry(HttpHeaderEntry * e);
     void insertEntry(HttpHeaderEntry * e);
-    String getList(http_hdr_type id) const;
-    bool getList(http_hdr_type id, String *s) const;
-    String getStrOrList(http_hdr_type id) const;
+    String getList(Http::HdrType id) const;
+    bool getList(Http::HdrType id, String *s) const;
     bool conflictingContentLength() const { return conflictingContentLength_; }
+    String getStrOrList(Http::HdrType id) const;
+    String getByName(const SBuf &name) const;
     String getByName(const char *name) const;
-    /// sets value and returns true iff a [possibly empty] named field is there
-    bool getByNameIfPresent(const char *name, String &value) const;
+    String getById(Http::HdrType id) const;
+    /// returns true iff a [possibly empty] field identified by id is there
+    /// when returning true, also sets the `result` parameter (if it is not nil)
+    bool getByIdIfPresent(Http::HdrType id, String *result) const;
+    /// returns true iff a [possibly empty] named field is there
+    /// when returning true, also sets the `value` parameter (if it is not nil)
+    bool hasNamed(const SBuf &s, String *value = 0) const;
+    bool hasNamed(const char *name, int namelen, String *value = 0) const;
     String getByNameListMember(const char *name, const char *member, const char separator) const;
-    String getListMember(http_hdr_type id, const char *member, const char separator) const;
-    int has(http_hdr_type id) const;
-    void putInt(http_hdr_type id, int number);
-    void putInt64(http_hdr_type id, int64_t number);
-    void putTime(http_hdr_type id, time_t htime);
-    void insertTime(http_hdr_type id, time_t htime);
-    void putStr(http_hdr_type id, const char *str);
+    String getListMember(Http::HdrType id, const char *member, const char separator) const;
+    int has(Http::HdrType id) const;
+    /// Appends "this cache" information to VIA header field.
+    /// Takes the initial VIA value from "from" parameter, if provided.
+    void addVia(const AnyP::ProtocolVersion &ver, const HttpHeader *from = 0);
+    void putInt(Http::HdrType id, int number);
+    void putInt64(Http::HdrType id, int64_t number);
+    void putTime(Http::HdrType id, time_t htime);
+    void putStr(Http::HdrType id, const char *str);
     void putAuth(const char *auth_scheme, const char *realm);
     void putCc(const HttpHdrCc * cc);
     void putContRange(const HttpHdrContRange * cr);
     void putRange(const HttpHdrRange * range);
     void putSc(HttpHdrSc *sc);
     void putWarning(const int code, const char *const text); ///< add a Warning header
     void putExt(const char *name, const char *value);
-    int getInt(http_hdr_type id) const;
-    int64_t getInt64(http_hdr_type id) const;
-    time_t getTime(http_hdr_type id) const;
-    const char *getStr(http_hdr_type id) const;
-    const char *getLastStr(http_hdr_type id) const;
+    int getInt(Http::HdrType id) const;
+    int64_t getInt64(Http::HdrType id) const;
+    time_t getTime(Http::HdrType id) const;
+    const char *getStr(Http::HdrType id) const;
+    const char *getLastStr(Http::HdrType id) const;
     HttpHdrCc *getCc() const;
     HttpHdrRange *getRange() const;
     HttpHdrSc *getSc() const;
     HttpHdrContRange *getContRange() const;
-    const char *getAuth(http_hdr_type id, const char *auth_scheme) const;
-    ETag getETag(http_hdr_type id) const;
-    TimeOrTag getTimeOrTag(http_hdr_type id) const;
-    int hasListMember(http_hdr_type id, const char *member, const char separator) const;
+    const char *getAuth(Http::HdrType id, const char *auth_scheme) const;
+    ETag getETag(Http::HdrType id) const;
+    TimeOrTag getTimeOrTag(Http::HdrType id) const;
+    int hasListMember(Http::HdrType id, const char *member, const char separator) const;
     int hasByNameListMember(const char *name, const char *member, const char separator) const;
     void removeHopByHopEntries();
     inline bool chunked() const; ///< whether message uses chunked Transfer-Encoding
 
     /* protected, do not use these, use interface functions instead */
     std::vector<HttpHeaderEntry *> entries;     /**< parsed fields in raw format */
