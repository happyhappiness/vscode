
    /* Interface functions */
    void clean();
    void append(const HttpHeader * src);
    bool update(HttpHeader const *fresh);
    void compact();
    int reset();
    int parse(const char *header_start, const char *header_end);
    void packInto(Packer * p, bool mask_sensitive_info=false) const;
    HttpHeaderEntry *getEntry(HttpHeaderPos * pos) const;
    HttpHeaderEntry *findEntry(http_hdr_type id) const;
    int delByName(const char *name);
    int delById(http_hdr_type id);
    void delAt(HttpHeaderPos pos, int &headers_deleted);
    void refreshMask();
    void addEntry(HttpHeaderEntry * e);
    void insertEntry(HttpHeaderEntry * e);
    String getList(http_hdr_type id) const;
    bool getList(http_hdr_type id, String *s) const;
    String getStrOrList(http_hdr_type id) const;
    bool conflictingContentLength() const { return conflictingContentLength_; }
    String getByName(const char *name) const;
    /// sets value and returns true iff a [possibly empty] named field is there
    bool getByNameIfPresent(const char *name, String &value) const;
    String getByNameListMember(const char *name, const char *member, const char separator) const;
    String getListMember(http_hdr_type id, const char *member, const char separator) const;
    int has(http_hdr_type id) const;
    void putInt(http_hdr_type id, int number);
    void putInt64(http_hdr_type id, int64_t number);
    void putTime(http_hdr_type id, time_t htime);
    void insertTime(http_hdr_type id, time_t htime);
    void putStr(http_hdr_type id, const char *str);
    void putAuth(const char *auth_scheme, const char *realm);
    void putCc(const HttpHdrCc * cc);
    void putContRange(const HttpHdrContRange * cr);
    void putRange(const HttpHdrRange * range);
    void putSc(HttpHdrSc *sc);
    void putWarning(const int code, const char *const text); ///< add a Warning header
    void putExt(const char *name, const char *value);
    int getInt(http_hdr_type id) const;
    int64_t getInt64(http_hdr_type id) const;
    time_t getTime(http_hdr_type id) const;
    const char *getStr(http_hdr_type id) const;
    const char *getLastStr(http_hdr_type id) const;
    HttpHdrCc *getCc() const;
    HttpHdrRange *getRange() const;
    HttpHdrSc *getSc() const;
    HttpHdrContRange *getContRange() const;
    const char *getAuth(http_hdr_type id, const char *auth_scheme) const;
    ETag getETag(http_hdr_type id) const;
    TimeOrTag getTimeOrTag(http_hdr_type id) const;
    int hasListMember(http_hdr_type id, const char *member, const char separator) const;
    int hasByNameListMember(const char *name, const char *member, const char separator) const;
    void removeHopByHopEntries();
    inline bool chunked() const; ///< whether message uses chunked Transfer-Encoding

    /* protected, do not use these, use interface functions instead */
    std::vector<HttpHeaderEntry *> entries;     /**< parsed fields in raw format */
