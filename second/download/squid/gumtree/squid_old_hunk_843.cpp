StoreEntry *
MemStore::get(const cache_key *key)
{
    if (!map)
        return NULL;

    // XXX: replace sfileno with a bigger word (sfileno is only for cache_dirs)
    sfileno index;
    const Ipc::StoreMapSlot *const slot = map->openForReading(key, index);
    if (!slot)
        return NULL;

    const Ipc::StoreMapSlot::Basics &basics = slot->basics;
    const MemStoreMap::Extras &extras = map->extras(index);

    // create a brand new store entry and initialize it with stored info
    StoreEntry *e = new StoreEntry();
    e->lock_count = 0;

    e->swap_file_sz = basics.swap_file_sz;
    e->lastref = basics.lastref;
    e->timestamp = basics.timestamp;
    e->expires = basics.expires;
    e->lastmod = basics.lastmod;
    e->refcount = basics.refcount;
    e->flags = basics.flags;

    e->store_status = STORE_OK;
    e->mem_status = IN_MEMORY; // setMemStatus(IN_MEMORY) requires mem_obj
    //e->swap_status = set in StoreEntry constructor to SWAPOUT_NONE;
    e->ping_status = PING_NONE;

    EBIT_SET(e->flags, ENTRY_CACHABLE);
    EBIT_CLR(e->flags, RELEASE_REQUEST);
    EBIT_CLR(e->flags, KEY_PRIVATE);
    EBIT_SET(e->flags, ENTRY_VALIDATED);

    const bool copied = copyFromShm(*e, extras);

    // we copied everything we could to local memory; no more need to lock
    map->closeForReading(index);

    if (copied) {
        e->hashInsert(key);
        return e;
    }

    debugs(20, 3, HERE << "mem-loading failed; freeing " << index);
    map->free(index); // do not let others into the same trap
    return NULL;
}

void
MemStore::get(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
{
    // XXX: not needed but Store parent forces us to implement this
    fatal("MemStore::get(key,callback,data) should not be called");
}

bool
MemStore::copyFromShm(StoreEntry &e, const MemStoreMap::Extras &extras)
{
    const Ipc::Mem::PageId &page = extras.page;

    StoreIOBuffer sourceBuf(extras.storedSize, 0,
                            static_cast<char*>(PagePointer(page)));

    // XXX: We do not know the URLs yet, only the key, but we need to parse and
    // store the response for the Root().get() callers to be happy because they
    // expect IN_MEMORY entries to already have the response headers and body.
    // At least one caller calls createMemObject() if there is not one, so
    // we hide the true object until that happens (to avoid leaking TBD URLs).
    e.createMemObject("TBD", "TBD");

    // emulate the usual Store code but w/o inapplicable checks and callbacks:

    // from store_client::readBody():
    HttpReply *rep = (HttpReply *)e.getReply();
    const ssize_t end = headersEnd(sourceBuf.data, sourceBuf.length);
    if (!rep->parseCharBuf(sourceBuf.data, end)) {
        debugs(20, DBG_IMPORTANT, "Could not parse mem-cached headers: " << e);
        return false;
    }
    // local memory stores both headers and body
    e.mem_obj->object_sz = sourceBuf.length; // from StoreEntry::complete()

    storeGetMemSpace(sourceBuf.length); // from StoreEntry::write()

    assert(e.mem_obj->data_hdr.write(sourceBuf)); // from MemObject::write()
    const int64_t written = e.mem_obj->endOffset();
    // we should write all because StoreEntry::write() never fails
    assert(written >= 0 &&
           static_cast<size_t>(written) == sourceBuf.length);
    // would be nice to call validLength() here, but it needs e.key

    debugs(20, 7, HERE << "mem-loaded all " << written << " bytes of " << e <<
           " from " << page);

    e.hideMemObject();

    return true;
}

bool
MemStore::keepInLocalMemory(const StoreEntry &e) const
{
    if (!e.memoryCachable()) {
        debugs(20, 7, HERE << "Not memory cachable: " << e);
        return false; // will not cache due to entry state or properties
    }

    assert(e.mem_obj);
    const int64_t loadedSize = e.mem_obj->endOffset();
    const int64_t expectedSize = e.mem_obj->expectedReplySize(); // may be < 0
    const int64_t ramSize = max(loadedSize, expectedSize);

    if (ramSize > static_cast<int64_t>(Config.Store.maxInMemObjSize)) {
        debugs(20, 5, HERE << "Too big max(" <<
               loadedSize << ", " << expectedSize << "): " << e);
        return false; // will not cache due to cachable entry size limits
    }

    if (!willFit(ramSize)) {
        debugs(20, 5, HERE << "Wont fit max(" <<
               loadedSize << ", " << expectedSize << "): " << e);
        return false; // will not cache due to memory cache slot limit
    }

    return true;
}

void
MemStore::considerKeeping(StoreEntry &e)
{
    if (!keepInLocalMemory(e))
        return;

    // since we copy everything at once, we can only keep complete entries
    if (e.store_status != STORE_OK) {
        debugs(20, 7, HERE << "Incomplete: " << e);
        return;
    }

    assert(e.mem_obj);

    const int64_t loadedSize = e.mem_obj->endOffset();
    const int64_t expectedSize = e.mem_obj->expectedReplySize();

    // objects of unknown size are not allowed into memory cache, for now
    if (expectedSize < 0) {
        debugs(20, 5, HERE << "Unknown expected size: " << e);
        return;
    }

    // since we copy everything at once, we can only keep fully loaded entries
    if (loadedSize != expectedSize) {
        debugs(20, 7, HERE << "partially loaded: " << loadedSize << " != " <<
               expectedSize);
        return;
    }

    if (e.mem_obj->vary_headers) {
        // XXX: We must store/load SerialisedMetaData to cache Vary in RAM
        debugs(20, 5, "Vary not yet supported: " << e.mem_obj->vary_headers);
        return;
    }

    keep(e); // may still fail
}

bool
MemStore::willFit(int64_t need) const
{
    return need <= static_cast<int64_t>(Ipc::Mem::PageSize());
}

/// allocates map slot and calls copyToShm to store the entry in shared memory
void
MemStore::keep(StoreEntry &e)
{
    if (!map) {
        debugs(20, 5, HERE << "No map to mem-cache " << e);
        return;
    }

    sfileno index = 0;
    Ipc::StoreMapSlot *slot = map->openForWriting(reinterpret_cast<const cache_key *>(e.key), index);
    if (!slot) {
        debugs(20, 5, HERE << "No room in mem-cache map to index " << e);
        return;
    }

    MemStoreMap::Extras &extras = map->extras(index);
    if (copyToShm(e, extras)) {
        slot->set(e);
        map->closeForWriting(index, false);
    } else {
        map->abortIo(index);
    }
}

/// uses mem_hdr::copy() to copy local data to shared memory
bool
MemStore::copyToShm(StoreEntry &e, MemStoreMap::Extras &extras)
{
    Ipc::Mem::PageId page;
    if (!Ipc::Mem::GetPage(Ipc::Mem::PageId::cachePage, page)) {
        debugs(20, 5, HERE << "No mem-cache page for " << e);
        return false; // GetPage is responsible for any cleanup on failures
    }

    const int64_t bufSize = Ipc::Mem::PageSize();
    const int64_t eSize = e.mem_obj->endOffset();

    StoreIOBuffer sharedSpace(bufSize, 0,
                              static_cast<char*>(PagePointer(page)));

    // check that we kept everything or purge incomplete/sparse cached entry
    const ssize_t copied = e.mem_obj->data_hdr.copy(sharedSpace);
    if (eSize != copied) {
        debugs(20, 2, HERE << "Failed to mem-cache " << e << ": " <<
               eSize << "!=" << copied);
        // cleanup
        PutPage(page);
        return false;
    }

    debugs(20, 7, HERE << "mem-cached all " << eSize << " bytes of " << e <<
           " in " << page);

    theCurrentSize += Ipc::Mem::PageSize();
    // remember storage location and size
    extras.page = page;
    extras.storedSize = copied;
    return true;
}

void
MemStore::cleanReadable(const sfileno fileno)
{
    Ipc::Mem::PutPage(map->extras(fileno).page);
    theCurrentSize -= Ipc::Mem::PageSize();
}

/// calculates maximum number of entries we need to store and map
int64_t
MemStore::EntryLimit()
{
    if (!Config.memShared || !Config.memMaxSize)
        return 0; // no memory cache configured

    const int64_t entrySize = Ipc::Mem::PageSize(); // for now
    const int64_t entryLimit = Config.memMaxSize / entrySize;
    return entryLimit;
}

/// reports our needs for shared memory pages to Ipc::Mem::Pages
class MemStoreClaimMemoryNeedsRr: public RegisteredRunner
{
public:
    /* RegisteredRunner API */
    virtual void run(const RunnerRegistry &r);
};

RunnerRegistrationEntry(rrClaimMemoryNeeds, MemStoreClaimMemoryNeedsRr);

void
MemStoreClaimMemoryNeedsRr::run(const RunnerRegistry &)
{
    Ipc::Mem::NotePageNeed(Ipc::Mem::PageId::cachePage, MemStore::EntryLimit());
}

/// decides whether to use a shared memory cache or checks its configuration
class MemStoreCfgRr: public ::RegisteredRunner
{
public:
    /* RegisteredRunner API */
    virtual void run(const RunnerRegistry &);
};

RunnerRegistrationEntry(rrFinalizeConfig, MemStoreCfgRr);

void MemStoreCfgRr::run(const RunnerRegistry &r)
{
    // decide whether to use a shared memory cache if the user did not specify
    if (!Config.memShared.configured()) {
        Config.memShared.configure(Ipc::Atomic::Enabled() &&
                                   Ipc::Mem::Segment::Enabled() && UsingSmp() &&
                                   Config.memMaxSize > 0);
