 public:
     static DeferredRead::DeferrableRead DeferReader;
     bool checkDeferRead(int fd) const;
 
     virtual const char *getMD5Text() const;
     StoreEntry();
-    StoreEntry(const char *url, const char *log_url);
     virtual ~StoreEntry();
 
     virtual HttpReply const *getReply() const;
     virtual void write (StoreIOBuffer);
-    virtual _SQUID_INLINE_ bool isEmpty() const;
+
+    /** Check if the Store entry is emtpty
+     * \retval true   Store contains 0 bytes of data.
+     * \retval false  Store contains 1 or more bytes of data.
+     * \retval false  Store contains negative content !!!!!!
+     */
+    virtual bool isEmpty() const {
+        assert (mem_obj);
+        return mem_obj->endOffset() == 0;
+    }
     virtual bool isAccepting() const;
     virtual size_t bytesWanted(Range<size_t> const aRange, bool ignoreDelayPool = false) const;
+    /// flags [truncated or too big] entry with ENTRY_BAD_LENGTH and releases it
+    void lengthWentBad(const char *reason);
     virtual void complete();
     virtual store_client_t storeClientType() const;
     virtual char const *getSerialisedMetaData();
+    /// Store a prepared error response. MemObject locks the reply object.
+    void storeErrorResponse(HttpReply *reply);
     void replaceHttpReply(HttpReply *, bool andStartWriting = true);
     void startWriting(); ///< pack and write reply headers and, maybe, body
     /// whether we may start writing to disk (now or in the future)
     virtual bool mayStartSwapOut();
     virtual void trimMemory(const bool preserveSwappable);
+
+    // called when a decision to cache in memory has been made
+    void memOutDecision(const bool willCacheInRam);
+    // called when a decision to cache on disk has been made
+    void swapOutDecision(const MemObject::SwapOut::Decision &decision);
+
     void abort();
     void unlink();
-    void makePublic();
+    void makePublic(const KeyScope keyScope = ksDefault);
     void makePrivate();
-    void setPublicKey();
+    void setPublicKey(const KeyScope keyScope = ksDefault);
+    /// Resets existing public key to a public key with default scope,
+    /// releasing the old default-scope entry (if any).
+    /// Does nothing if the existing public key already has default scope.
+    void clearPublicKeyScope();
     void setPrivateKey();
     void expireNow();
     void releaseRequest();
     void negativeCache();
-    void cacheNegatively();		/** \todo argh, why both? */
+    void cacheNegatively();     /** \todo argh, why both? */
     void invokeHandlers();
     void purgeMem();
     void cacheInMemory(); ///< start or continue storing in memory cache
     void swapOut();
     /// whether we are in the process of writing this entry to disk
     bool swappingOut() const { return swap_status == SWAPOUT_WRITING; }
     void swapOutFileClose(int how);
     const char *url() const;
-    int checkCachable();
+    /// Satisfies cachability requirements shared among disk and RAM caches.
+    /// Encapsulates common checks of mayStartSwapOut() and memoryCachable().
+    /// TODO: Rename and make private so only those two methods can call this.
+    bool checkCachable();
     int checkNegativeHit() const;
     int locked() const;
     int validToSend() const;
-    bool memoryCachable() const; ///< may be cached in memory
-    void createMemObject(const char *, const char *);
-    void hideMemObject(); ///< no mem_obj for callers until createMemObject
+    bool memoryCachable(); ///< checkCachable() and can be cached in memory
+
+    /// if needed, initialize mem_obj member w/o URI-related information
+    MemObject *makeMemObject();
+
+    /// initialize mem_obj member (if needed) and supply URI-related info
+    void createMemObject(const char *storeId, const char *logUri, const HttpRequestMethod &aMethod);
+
     void dump(int debug_lvl) const;
     void hashDelete();
     void hashInsert(const cache_key *);
     void registerAbort(STABH * cb, void *);
     void reset();
     void setMemStatus(mem_status_t);
-    void timestampsSet();
+    bool timestampsSet();
     void unregisterAbort();
     void destroyMemObject();
     int checkTooSmall();
 
     void delayAwareRead(const Comm::ConnectionPointer &conn, char *buf, int len, AsyncCall::Pointer callback);
 
     void setNoDelay (bool const);
-    bool modifiedSince(HttpRequest * request) const;
+    void lastModified(const time_t when) { lastModified_ = when; }
+    /// \returns entry's 'effective' modification time
+    time_t lastModified() const {
+        // may still return -1 if timestamp is not set
+        return lastModified_ < 0 ? timestamp : lastModified_;
+    }
+    /// \returns a formatted string with entry's timestamps
+    const char *describeTimestamps() const;
+    // TODO: consider removing currently unsupported imslen parameter
+    bool modifiedSince(const time_t ims, const int imslen = -1) const;
     /// has ETag matching at least one of the If-Match etags
     bool hasIfMatchEtag(const HttpRequest &request) const;
     /// has ETag matching at least one of the If-None-Match etags
     bool hasIfNoneMatchEtag(const HttpRequest &request) const;
     /// whether this entry has an ETag; if yes, puts ETag value into parameter
     bool hasEtag(ETag &etag) const;
 
     /** What store does this entry belong too ? */
     virtual RefCount<SwapDir> store() const;
 
     MemObject *mem_obj;
-    MemObject *hidden_mem_obj; ///< mem_obj created before URLs were known
     RemovalPolicyNode repl;
     /* START OF ON-DISK STORE_META_STD TLV field */
     time_t timestamp;
     time_t lastref;
     time_t expires;
-    time_t lastmod;
+private:
+    time_t lastModified_; ///< received Last-Modified value or -1; use lastModified()
+public:
     uint64_t swap_file_sz;
     uint16_t refcount;
     uint16_t flags;
     /* END OF ON-DISK STORE_META_STD */
 
     /// unique ID inside a cache_dir for swapped out entries; -1 for others
     sfileno swap_filen:25; // keep in sync with SwapFilenMax
 
     sdirno swap_dirn:7;
 
-    unsigned short lock_count;		/* Assume < 65536! */
-
     mem_status_t mem_status:3;
 
     ping_status_t ping_status:3;
 
     store_status_t store_status:3;
 
