public:
    static DeferredRead::DeferrableRead DeferReader;
    bool checkDeferRead(int fd) const;

    virtual const char *getMD5Text() const;
    StoreEntry();
    StoreEntry(const char *url, const char *log_url);
    virtual ~StoreEntry();

    virtual HttpReply const *getReply() const;
    virtual void write (StoreIOBuffer);
    virtual _SQUID_INLINE_ bool isEmpty() const;
    virtual bool isAccepting() const;
    virtual size_t bytesWanted(Range<size_t> const aRange, bool ignoreDelayPool = false) const;
    virtual void complete();
    virtual store_client_t storeClientType() const;
    virtual char const *getSerialisedMetaData();
    void replaceHttpReply(HttpReply *, bool andStartWriting = true);
    void startWriting(); ///< pack and write reply headers and, maybe, body
    /// whether we may start writing to disk (now or in the future)
    virtual bool mayStartSwapOut();
    virtual void trimMemory(const bool preserveSwappable);
    void abort();
    void unlink();
    void makePublic();
    void makePrivate();
    void setPublicKey();
    void setPrivateKey();
    void expireNow();
    void releaseRequest();
    void negativeCache();
    void cacheNegatively();		/** \todo argh, why both? */
    void invokeHandlers();
    void purgeMem();
    void cacheInMemory(); ///< start or continue storing in memory cache
    void swapOut();
    /// whether we are in the process of writing this entry to disk
    bool swappingOut() const { return swap_status == SWAPOUT_WRITING; }
    void swapOutFileClose(int how);
    const char *url() const;
    int checkCachable();
    int checkNegativeHit() const;
    int locked() const;
    int validToSend() const;
    bool memoryCachable() const; ///< may be cached in memory
    void createMemObject(const char *, const char *);
    void hideMemObject(); ///< no mem_obj for callers until createMemObject
    void dump(int debug_lvl) const;
    void hashDelete();
    void hashInsert(const cache_key *);
    void registerAbort(STABH * cb, void *);
    void reset();
    void setMemStatus(mem_status_t);
    void timestampsSet();
    void unregisterAbort();
    void destroyMemObject();
    int checkTooSmall();

    void delayAwareRead(const Comm::ConnectionPointer &conn, char *buf, int len, AsyncCall::Pointer callback);

    void setNoDelay (bool const);
    bool modifiedSince(HttpRequest * request) const;
    /// has ETag matching at least one of the If-Match etags
    bool hasIfMatchEtag(const HttpRequest &request) const;
    /// has ETag matching at least one of the If-None-Match etags
    bool hasIfNoneMatchEtag(const HttpRequest &request) const;
    /// whether this entry has an ETag; if yes, puts ETag value into parameter
    bool hasEtag(ETag &etag) const;

    /** What store does this entry belong too ? */
    virtual RefCount<SwapDir> store() const;

    MemObject *mem_obj;
    MemObject *hidden_mem_obj; ///< mem_obj created before URLs were known
    RemovalPolicyNode repl;
    /* START OF ON-DISK STORE_META_STD TLV field */
    time_t timestamp;
    time_t lastref;
    time_t expires;
    time_t lastmod;
    uint64_t swap_file_sz;
    uint16_t refcount;
    uint16_t flags;
    /* END OF ON-DISK STORE_META_STD */

    /// unique ID inside a cache_dir for swapped out entries; -1 for others
    sfileno swap_filen:25; // keep in sync with SwapFilenMax

    sdirno swap_dirn:7;

    unsigned short lock_count;		/* Assume < 65536! */

    mem_status_t mem_status:3;

    ping_status_t ping_status:3;

    store_status_t store_status:3;

