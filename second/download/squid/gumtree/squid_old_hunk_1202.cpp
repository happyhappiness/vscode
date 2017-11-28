    const char *getMD5Text() const;
    HttpReply const *getReply() const { return NULL; }
    void write (StoreIOBuffer) {}

    bool isEmpty () const {return true;}

    virtual size_t bytesWanted(Range<size_t> const aRange, bool ignoreDelayPool = false) const { return aRange.end; }

    void operator delete(void *address);
    void complete() {}

private:
    store_client_t storeClientType() const {return STORE_MEM_CLIENT;}

    char const *getSerialisedMetaData();
    virtual bool mayStartSwapOut() { return false; }

    void trimMemory(const bool preserveSwappable) {}

    static NullStoreEntry _instance;
};

/// \ingroup StoreAPI
typedef void (*STOREGETCLIENT) (StoreEntry *, void *cbdata);

/**
 \ingroup StoreAPI
 * Abstract base class that will replace the whole store and swapdir interface.
 */
class Store : public RefCountable
{

public:
    /** The root store */
    static Store &Root() {
        if (CurrentRoot == NULL)
            fatal("No Store Root has been set");
        return *CurrentRoot;
    }
    static void Root(Store *);
    static void Root(RefCount<Store>);
    static void Stats(StoreEntry * output);
    static void Maintain(void *unused);

    virtual ~Store() {}

    /** Handle pending callbacks - called by the event loop. */
    virtual int callback() = 0;

    /** create the resources needed for this store to operate */
    virtual void create();

    /**
     * Notify this store that its disk is full.
     \todo XXX move into a protected api call between store files and their stores, rather than a top level api call
     */
    virtual void diskFull();

    /** Retrieve a store entry from the store */
    virtual StoreEntry * get(const cache_key *) = 0;

    /** \todo imeplement the async version */
    virtual void get(String const key , STOREGETCLIENT callback, void *cbdata) = 0;

    /* prepare the store for use. The store need not be usable immediately,
     * it should respond to readable() and writable() with true as soon
     * as it can provide those services
     */
    virtual void init() = 0;

    /**
     * The maximum size the store will support in normal use. Inaccuracy is permitted,
     * but may throw estimates for memory etc out of whack.
     */
    virtual uint64_t maxSize() const = 0;

    /** The minimum size the store will shrink to via normal housekeeping */
    virtual uint64_t minSize() const = 0;

    /** current store size */
    virtual uint64_t currentSize() const = 0;

    /** the total number of objects stored */
    virtual uint64_t currentCount() const = 0;

    /** the maximum object size that can be stored, -1 if unlimited */
    virtual int64_t maxObjectSize() const = 0;

    /// collect cache storage-related statistics
    virtual void getStats(StoreInfoStats &stats) const = 0;

    /**
     * Output stats to the provided store entry.
     \todo make these calls asynchronous
     */
    virtual void stat(StoreEntry &) const = 0;

    /** Sync the store prior to shutdown */
    virtual void sync();

    /** remove a Store entry from the store */
    virtual void unlink (StoreEntry &);

    /* search in the store */
    virtual StoreSearch *search(String const url, HttpRequest *) = 0;

    /* pulled up from SwapDir for migration.... probably do not belong here */
    virtual void reference(StoreEntry &) = 0;   /* Reference this object */

    /// Undo reference(), returning false iff idle e should be destroyed
    virtual bool dereference(StoreEntry &e, bool wantsLocalMemory) = 0;

    virtual void maintain() = 0; /* perform regular maintenance should be private and self registered ... */

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // to avoid casting Root() to StoreController until Root() API is fixed.
    /// informs stores that this entry will be eventually unlinked
    virtual void markForUnlink(StoreEntry &e) {}

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // because test cases use non-StoreController derivatives as Root
    /// called when the entry is no longer needed by any transaction
    virtual void handleIdleEntry(StoreEntry &e) {}

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // because test cases use non-StoreController derivatives as Root
    /// called to get rid of no longer needed entry data in RAM, if any
    virtual void memoryOut(StoreEntry &e, const bool preserveSwappable) {}

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // to avoid casting Root() to StoreController until Root() API is fixed.
    /// makes the entry available for collapsing future requests
    virtual void allowCollapsing(StoreEntry *e, const RequestFlags &reqFlags, const HttpRequestMethod &reqMethod) {}

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // to avoid casting Root() to StoreController until Root() API is fixed.
    /// marks the entry completed for collapsed requests
    virtual void transientsCompleteWriting(StoreEntry &e) {}

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // to avoid casting Root() to StoreController until Root() API is fixed.
    /// Update local intransit entry after changes made by appending worker.
    virtual void syncCollapsed(const sfileno xitIndex) {}

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // to avoid casting Root() to StoreController until Root() API is fixed.
    /// calls Root().transients->abandon() if transients are tracked
    virtual void transientsAbandon(StoreEntry &e) {}

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // to avoid casting Root() to StoreController until Root() API is fixed.
    /// number of the transient entry readers some time ago
    virtual int transientReaders(const StoreEntry &e) const { return 0; }

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // to avoid casting Root() to StoreController until Root() API is fixed.
    /// disassociates the entry from the intransit table
    virtual void transientsDisconnect(MemObject &mem_obj) {}

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // to avoid casting Root() to StoreController until Root() API is fixed.
    /// removes the entry from the memory cache
    virtual void memoryUnlink(StoreEntry &e) {}

    // XXX: This method belongs to Store::Root/StoreController, but it is here
    // to avoid casting Root() to StoreController until Root() API is fixed.
    /// disassociates the entry from the memory cache, preserving cached data
    virtual void memoryDisconnect(StoreEntry &e) {}

    /// If the entry is not found, return false. Otherwise, return true after
    /// tying the entry to this cache and setting inSync to updateCollapsed().
    virtual bool anchorCollapsed(StoreEntry &collapsed, bool &inSync) { return false; }

    /// update a local collapsed entry with fresh info from this cache (if any)
    virtual bool updateCollapsed(StoreEntry &collapsed) { return false; }

    /// whether this storage is capable of serving multiple workers
    virtual bool smpAware() const = 0;

private:
    static RefCount<Store> CurrentRoot;
};

/// \ingroup StoreAPI
typedef RefCount<Store> StorePointer;

/// \ingroup StoreAPI
size_t storeEntryInUse();

/// \ingroup StoreAPI
const char *storeEntryFlags(const StoreEntry *);

/// \ingroup StoreAPI
