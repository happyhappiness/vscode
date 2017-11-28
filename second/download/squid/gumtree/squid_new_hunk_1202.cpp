    const char *getMD5Text() const;
    HttpReply const *getReply() const { return NULL; }
    void write (StoreIOBuffer) {}

    bool isEmpty () const {return true;}

    virtual size_t bytesWanted(Range<size_t> const aRange, bool) const { return aRange.end; }

    void operator delete(void *address);
    void complete() {}

private:
    store_client_t storeClientType() const {return STORE_MEM_CLIENT;}

    char const *getSerialisedMetaData();
    virtual bool mayStartSwapOut() { return false; }

    void trimMemory(const bool) {}

    static NullStoreEntry _instance;
};

/// \ingroup StoreAPI
typedef void (*STOREGETCLIENT) (StoreEntry *, void *cbdata);

namespace Store {
void Stats(StoreEntry *output);
void Maintain(void *unused);
};

/// \ingroup StoreAPI
size_t storeEntryInUse();

/// \ingroup StoreAPI
const char *storeEntryFlags(const StoreEntry *);

/// \ingroup StoreAPI
