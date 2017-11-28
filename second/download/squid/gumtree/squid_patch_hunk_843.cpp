 StoreEntry *
 MemStore::get(const cache_key *key)
 {
     if (!map)
         return NULL;
 
-    // XXX: replace sfileno with a bigger word (sfileno is only for cache_dirs)
     sfileno index;
-    const Ipc::StoreMapSlot *const slot = map->openForReading(key, index);
+    const Ipc::StoreMapAnchor *const slot = map->openForReading(key, index);
     if (!slot)
         return NULL;
 
-    const Ipc::StoreMapSlot::Basics &basics = slot->basics;
-    const MemStoreMap::Extras &extras = map->extras(index);
-
     // create a brand new store entry and initialize it with stored info
     StoreEntry *e = new StoreEntry();
-    e->lock_count = 0;
 
-    e->swap_file_sz = basics.swap_file_sz;
-    e->lastref = basics.lastref;
-    e->timestamp = basics.timestamp;
-    e->expires = basics.expires;
-    e->lastmod = basics.lastmod;
-    e->refcount = basics.refcount;
-    e->flags = basics.flags;
-
-    e->store_status = STORE_OK;
-    e->mem_status = IN_MEMORY; // setMemStatus(IN_MEMORY) requires mem_obj
-    //e->swap_status = set in StoreEntry constructor to SWAPOUT_NONE;
-    e->ping_status = PING_NONE;
-
-    EBIT_SET(e->flags, ENTRY_CACHABLE);
-    EBIT_CLR(e->flags, RELEASE_REQUEST);
-    EBIT_CLR(e->flags, KEY_PRIVATE);
-    EBIT_SET(e->flags, ENTRY_VALIDATED);
+    // XXX: We do not know the URLs yet, only the key, but we need to parse and
+    // store the response for the Root().get() callers to be happy because they
+    // expect IN_MEMORY entries to already have the response headers and body.
+    e->makeMemObject();
 
-    const bool copied = copyFromShm(*e, extras);
+    anchorEntry(*e, index, *slot);
 
-    // we copied everything we could to local memory; no more need to lock
-    map->closeForReading(index);
+    const bool copied = copyFromShm(*e, index, *slot);
 
     if (copied) {
         e->hashInsert(key);
         return e;
     }
 
     debugs(20, 3, HERE << "mem-loading failed; freeing " << index);
-    map->free(index); // do not let others into the same trap
+    map->freeEntry(index); // do not let others into the same trap
     return NULL;
 }
 
 void
 MemStore::get(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
 {
     // XXX: not needed but Store parent forces us to implement this
     fatal("MemStore::get(key,callback,data) should not be called");
 }
 
 bool
-MemStore::copyFromShm(StoreEntry &e, const MemStoreMap::Extras &extras)
+MemStore::anchorCollapsed(StoreEntry &collapsed, bool &inSync)
 {
-    const Ipc::Mem::PageId &page = extras.page;
+    if (!map)
+        return false;
 
-    StoreIOBuffer sourceBuf(extras.storedSize, 0,
-                            static_cast<char*>(PagePointer(page)));
+    sfileno index;
+    const Ipc::StoreMapAnchor *const slot = map->openForReading(
+            reinterpret_cast<cache_key*>(collapsed.key), index);
+    if (!slot)
+        return false;
 
-    // XXX: We do not know the URLs yet, only the key, but we need to parse and
-    // store the response for the Root().get() callers to be happy because they
-    // expect IN_MEMORY entries to already have the response headers and body.
-    // At least one caller calls createMemObject() if there is not one, so
-    // we hide the true object until that happens (to avoid leaking TBD URLs).
-    e.createMemObject("TBD", "TBD");
+    anchorEntry(collapsed, index, *slot);
+    inSync = updateCollapsedWith(collapsed, index, *slot);
+    return true; // even if inSync is false
+}
 
-    // emulate the usual Store code but w/o inapplicable checks and callbacks:
+bool
+MemStore::updateCollapsed(StoreEntry &collapsed)
+{
+    assert(collapsed.mem_obj);
 
-    // from store_client::readBody():
-    HttpReply *rep = (HttpReply *)e.getReply();
-    const ssize_t end = headersEnd(sourceBuf.data, sourceBuf.length);
-    if (!rep->parseCharBuf(sourceBuf.data, end)) {
-        debugs(20, DBG_IMPORTANT, "Could not parse mem-cached headers: " << e);
+    const sfileno index = collapsed.mem_obj->memCache.index;
+
+    // already disconnected from the cache, no need to update
+    if (index < 0)
+        return true;
+
+    if (!map)
         return false;
+
+    const Ipc::StoreMapAnchor &anchor = map->readableEntry(index);
+    return updateCollapsedWith(collapsed, index, anchor);
+}
+
+/// updates collapsed entry after its anchor has been located
+bool
+MemStore::updateCollapsedWith(StoreEntry &collapsed, const sfileno index, const Ipc::StoreMapAnchor &anchor)
+{
+    collapsed.swap_file_sz = anchor.basics.swap_file_sz;
+    const bool copied = copyFromShm(collapsed, index, anchor);
+    return copied;
+}
+
+/// anchors StoreEntry to an already locked map entry
+void
+MemStore::anchorEntry(StoreEntry &e, const sfileno index, const Ipc::StoreMapAnchor &anchor)
+{
+    const Ipc::StoreMapAnchor::Basics &basics = anchor.basics;
+
+    e.swap_file_sz = basics.swap_file_sz;
+    e.lastref = basics.lastref;
+    e.timestamp = basics.timestamp;
+    e.expires = basics.expires;
+    e.lastModified(basics.lastmod);
+    e.refcount = basics.refcount;
+    e.flags = basics.flags;
+
+    assert(e.mem_obj);
+    if (anchor.complete()) {
+        e.store_status = STORE_OK;
+        e.mem_obj->object_sz = e.swap_file_sz;
+        e.setMemStatus(IN_MEMORY);
+    } else {
+        e.store_status = STORE_PENDING;
+        assert(e.mem_obj->object_sz < 0);
+        e.setMemStatus(NOT_IN_MEMORY);
+    }
+    assert(e.swap_status == SWAPOUT_NONE); // set in StoreEntry constructor
+    e.ping_status = PING_NONE;
+
+    EBIT_CLR(e.flags, RELEASE_REQUEST);
+    EBIT_CLR(e.flags, KEY_PRIVATE);
+    EBIT_SET(e.flags, ENTRY_VALIDATED);
+
+    MemObject::MemCache &mc = e.mem_obj->memCache;
+    mc.index = index;
+    mc.io = MemObject::ioReading;
+}
+
+/// copies the entire entry from shared to local memory
+bool
+MemStore::copyFromShm(StoreEntry &e, const sfileno index, const Ipc::StoreMapAnchor &anchor)
+{
+    debugs(20, 7, "mem-loading entry " << index << " from " << anchor.start);
+    assert(e.mem_obj);
+
+    // emulate the usual Store code but w/o inapplicable checks and callbacks:
+
+    Ipc::StoreMapSliceId sid = anchor.start; // optimize: remember the last sid
+    bool wasEof = anchor.complete() && sid < 0;
+    int64_t sliceOffset = 0;
+    while (sid >= 0) {
+        const Ipc::StoreMapSlice &slice = map->readableSlice(index, sid);
+        // slice state may change during copying; take snapshots now
+        wasEof = anchor.complete() && slice.next < 0;
+        const Ipc::StoreMapSlice::Size wasSize = slice.size;
+
+        debugs(20, 9, "entry " << index << " slice " << sid << " eof " <<
+               wasEof << " wasSize " << wasSize << " <= " <<
+               anchor.basics.swap_file_sz << " sliceOffset " << sliceOffset <<
+               " mem.endOffset " << e.mem_obj->endOffset());
+
+        if (e.mem_obj->endOffset() < sliceOffset + wasSize) {
+            // size of the slice data that we already copied
+            const size_t prefixSize = e.mem_obj->endOffset() - sliceOffset;
+            assert(prefixSize <= wasSize);
+
+            const MemStoreMapExtras::Item &extra = extras->items[sid];
+
+            char *page = static_cast<char*>(PagePointer(extra.page));
+            const StoreIOBuffer sliceBuf(wasSize - prefixSize,
+                                         e.mem_obj->endOffset(),
+                                         page + prefixSize);
+            if (!copyFromShmSlice(e, sliceBuf, wasEof))
+                return false;
+            debugs(20, 9, "entry " << index << " copied slice " << sid <<
+                   " from " << extra.page << '+' << prefixSize);
+        }
+        // else skip a [possibly incomplete] slice that we copied earlier
+
+        // careful: the slice may have grown _and_ gotten the next slice ID!
+        if (slice.next >= 0) {
+            assert(!wasEof);
+            // here we know that slice.size may not change any more
+            if (wasSize >= slice.size) { // did not grow since we started copying
+                sliceOffset += wasSize;
+                sid = slice.next;
+            }
+        } else if (wasSize >= slice.size) { // did not grow
+            break;
+        }
     }
-    // local memory stores both headers and body
-    e.mem_obj->object_sz = sourceBuf.length; // from StoreEntry::complete()
 
-    storeGetMemSpace(sourceBuf.length); // from StoreEntry::write()
+    if (!wasEof) {
+        debugs(20, 7, "mem-loaded " << e.mem_obj->endOffset() << '/' <<
+               anchor.basics.swap_file_sz << " bytes of " << e);
+        return true;
+    }
+
+    debugs(20, 7, "mem-loaded all " << e.mem_obj->object_sz << '/' <<
+           anchor.basics.swap_file_sz << " bytes of " << e);
+
+    // from StoreEntry::complete()
+    e.mem_obj->object_sz = e.mem_obj->endOffset();
+    e.store_status = STORE_OK;
+    e.setMemStatus(IN_MEMORY);
 
-    assert(e.mem_obj->data_hdr.write(sourceBuf)); // from MemObject::write()
-    const int64_t written = e.mem_obj->endOffset();
-    // we should write all because StoreEntry::write() never fails
-    assert(written >= 0 &&
-           static_cast<size_t>(written) == sourceBuf.length);
+    assert(e.mem_obj->object_sz >= 0);
+    assert(static_cast<uint64_t>(e.mem_obj->object_sz) == anchor.basics.swap_file_sz);
     // would be nice to call validLength() here, but it needs e.key
 
-    debugs(20, 7, HERE << "mem-loaded all " << written << " bytes of " << e <<
-           " from " << page);
+    // we read the entire response into the local memory; no more need to lock
+    disconnect(e);
+    return true;
+}
 
-    e.hideMemObject();
+/// imports one shared memory slice into local memory
+bool
+MemStore::copyFromShmSlice(StoreEntry &e, const StoreIOBuffer &buf, bool eof)
+{
+    debugs(20, 7, "buf: " << buf.offset << " + " << buf.length);
+
+    // from store_client::readBody()
+    // parse headers if needed; they might span multiple slices!
+    HttpReply *rep = (HttpReply *)e.getReply();
+    if (rep->pstate < psParsed) {
+        // XXX: have to copy because httpMsgParseStep() requires 0-termination
+        MemBuf mb;
+        mb.init(buf.length+1, buf.length+1);
+        mb.append(buf.data, buf.length);
+        mb.terminate();
+        const int result = rep->httpMsgParseStep(mb.buf, buf.length, eof);
+        if (result > 0) {
+            assert(rep->pstate == psParsed);
+            EBIT_CLR(e.flags, ENTRY_FWD_HDR_WAIT);
+        } else if (result < 0) {
+            debugs(20, DBG_IMPORTANT, "Corrupted mem-cached headers: " << e);
+            return false;
+        } else { // more slices are needed
+            assert(!eof);
+        }
+    }
+    debugs(20, 7, "rep pstate: " << rep->pstate);
 
+    // local memory stores both headers and body so copy regardless of pstate
+    const int64_t offBefore = e.mem_obj->endOffset();
+    assert(e.mem_obj->data_hdr.write(buf)); // from MemObject::write()
+    const int64_t offAfter = e.mem_obj->endOffset();
+    // expect to write the entire buf because StoreEntry::write() never fails
+    assert(offAfter >= 0 && offBefore <= offAfter &&
+           static_cast<size_t>(offAfter - offBefore) == buf.length);
     return true;
 }
 
+/// whether we should cache the entry
 bool
-MemStore::keepInLocalMemory(const StoreEntry &e) const
+MemStore::shouldCache(StoreEntry &e) const
 {
+    if (e.mem_status == IN_MEMORY) {
+        debugs(20, 5, "already loaded from mem-cache: " << e);
+        return false;
+    }
+
+    if (e.mem_obj && e.mem_obj->memCache.offset > 0) {
+        debugs(20, 5, "already written to mem-cache: " << e);
+        return false;
+    }
+
     if (!e.memoryCachable()) {
         debugs(20, 7, HERE << "Not memory cachable: " << e);
         return false; // will not cache due to entry state or properties
     }
 
     assert(e.mem_obj);
-    const int64_t loadedSize = e.mem_obj->endOffset();
+
+    if (!e.mem_obj->vary_headers.isEmpty()) {
+        // XXX: We must store/load SerialisedMetaData to cache Vary in RAM
+        debugs(20, 5, "Vary not yet supported: " << e.mem_obj->vary_headers);
+        return false;
+    }
+
     const int64_t expectedSize = e.mem_obj->expectedReplySize(); // may be < 0
+
+    // objects of unknown size are not allowed into memory cache, for now
+    if (expectedSize < 0) {
+        debugs(20, 5, "Unknown expected size: " << e);
+        return false;
+    }
+
+    const int64_t loadedSize = e.mem_obj->endOffset();
     const int64_t ramSize = max(loadedSize, expectedSize);
 
-    if (ramSize > static_cast<int64_t>(Config.Store.maxInMemObjSize)) {
+    if (ramSize > maxObjectSize()) {
         debugs(20, 5, HERE << "Too big max(" <<
                loadedSize << ", " << expectedSize << "): " << e);
         return false; // will not cache due to cachable entry size limits
     }
 
-    if (!willFit(ramSize)) {
-        debugs(20, 5, HERE << "Wont fit max(" <<
-               loadedSize << ", " << expectedSize << "): " << e);
-        return false; // will not cache due to memory cache slot limit
+    if (!e.mem_obj->isContiguous()) {
+        debugs(20, 5, "not contiguous");
+        return false;
+    }
+
+    if (!map) {
+        debugs(20, 5, HERE << "No map to mem-cache " << e);
+        return false;
+    }
+
+    if (EBIT_TEST(e.flags, ENTRY_SPECIAL)) {
+        debugs(20, 5, "Not mem-caching ENTRY_SPECIAL " << e);
+        return false;
     }
 
     return true;
 }
 
-void
-MemStore::considerKeeping(StoreEntry &e)
+/// locks map anchor and preps to store the entry in shared memory
+bool
+MemStore::startCaching(StoreEntry &e)
 {
-    if (!keepInLocalMemory(e))
-        return;
+    sfileno index = 0;
+    Ipc::StoreMapAnchor *slot = map->openForWriting(reinterpret_cast<const cache_key *>(e.key), index);
+    if (!slot) {
+        debugs(20, 5, HERE << "No room in mem-cache map to index " << e);
+        return false;
+    }
 
-    // since we copy everything at once, we can only keep complete entries
-    if (e.store_status != STORE_OK) {
-        debugs(20, 7, HERE << "Incomplete: " << e);
+    assert(e.mem_obj);
+    e.mem_obj->memCache.index = index;
+    e.mem_obj->memCache.io = MemObject::ioWriting;
+    slot->set(e);
+    map->startAppending(index);
+    e.memOutDecision(true);
+    return true;
+}
+
+/// copies all local data to shared memory
+void
+MemStore::copyToShm(StoreEntry &e)
+{
+    // prevents remote readers from getting ENTRY_FWD_HDR_WAIT entries and
+    // not knowing when the wait is over
+    if (EBIT_TEST(e.flags, ENTRY_FWD_HDR_WAIT)) {
+        debugs(20, 5, "postponing copying " << e << " for ENTRY_FWD_HDR_WAIT");
         return;
     }
 
+    assert(map);
     assert(e.mem_obj);
 
-    const int64_t loadedSize = e.mem_obj->endOffset();
-    const int64_t expectedSize = e.mem_obj->expectedReplySize();
+    const int32_t index = e.mem_obj->memCache.index;
+    assert(index >= 0);
+    Ipc::StoreMapAnchor &anchor = map->writeableEntry(index);
 
-    // objects of unknown size are not allowed into memory cache, for now
-    if (expectedSize < 0) {
-        debugs(20, 5, HERE << "Unknown expected size: " << e);
-        return;
-    }
+    const int64_t eSize = e.mem_obj->endOffset();
+    if (e.mem_obj->memCache.offset >= eSize) {
+        debugs(20, 5, "postponing copying " << e << " for lack of news: " <<
+               e.mem_obj->memCache.offset << " >= " << eSize);
+        return; // nothing to do (yet)
+    }
+
+    if (anchor.start < 0) { // must allocate the very first slot for e
+        Ipc::Mem::PageId page;
+        anchor.start = reserveSapForWriting(page); // throws
+        extras->items[anchor.start].page = page;
+    }
+
+    lastWritingSlice = anchor.start;
+    const size_t sliceCapacity = Ipc::Mem::PageSize();
+
+    // fill, skip slices that are already full
+    // Optimize: remember lastWritingSlice in e.mem_obj
+    while (e.mem_obj->memCache.offset < eSize) {
+        Ipc::StoreMap::Slice &slice =
+            map->writeableSlice(e.mem_obj->memCache.index, lastWritingSlice);
+
+        if (slice.size >= sliceCapacity) {
+            if (slice.next >= 0) {
+                lastWritingSlice = slice.next;
+                continue;
+            }
 
-    // since we copy everything at once, we can only keep fully loaded entries
-    if (loadedSize != expectedSize) {
-        debugs(20, 7, HERE << "partially loaded: " << loadedSize << " != " <<
-               expectedSize);
-        return;
-    }
+            Ipc::Mem::PageId page;
+            slice.next = lastWritingSlice = reserveSapForWriting(page);
+            extras->items[lastWritingSlice].page = page;
+            debugs(20, 7, "entry " << index << " new slice: " << lastWritingSlice);
+        }
 
-    if (e.mem_obj->vary_headers) {
-        // XXX: We must store/load SerialisedMetaData to cache Vary in RAM
-        debugs(20, 5, "Vary not yet supported: " << e.mem_obj->vary_headers);
-        return;
+        copyToShmSlice(e, anchor);
     }
 
-    keep(e); // may still fail
+    debugs(20, 7, "mem-cached available " << eSize << " bytes of " << e);
 }
 
-bool
-MemStore::willFit(int64_t need) const
+/// copies at most one slice worth of local memory to shared memory
+void
+MemStore::copyToShmSlice(StoreEntry &e, Ipc::StoreMapAnchor &anchor)
 {
-    return need <= static_cast<int64_t>(Ipc::Mem::PageSize());
+    Ipc::StoreMap::Slice &slice =
+        map->writeableSlice(e.mem_obj->memCache.index, lastWritingSlice);
+
+    Ipc::Mem::PageId page = extras->items[lastWritingSlice].page;
+    assert(lastWritingSlice >= 0 && page);
+    debugs(20, 7, "entry " << e << " slice " << lastWritingSlice << " has " <<
+           page);
+
+    const int64_t bufSize = Ipc::Mem::PageSize();
+    const int64_t sliceOffset = e.mem_obj->memCache.offset % bufSize;
+    StoreIOBuffer sharedSpace(bufSize - sliceOffset, e.mem_obj->memCache.offset,
+                              static_cast<char*>(PagePointer(page)) + sliceOffset);
+
+    // check that we kept everything or purge incomplete/sparse cached entry
+    const ssize_t copied = e.mem_obj->data_hdr.copy(sharedSpace);
+    if (copied <= 0) {
+        debugs(20, 2, "Failed to mem-cache " << (bufSize - sliceOffset) <<
+               " bytes of " << e << " from " << e.mem_obj->memCache.offset <<
+               " in " << page);
+        throw TexcHere("data_hdr.copy failure");
+    }
+
+    debugs(20, 7, "mem-cached " << copied << " bytes of " << e <<
+           " from " << e.mem_obj->memCache.offset << " in " << page);
+
+    slice.size += copied;
+    e.mem_obj->memCache.offset += copied;
+    anchor.basics.swap_file_sz = e.mem_obj->memCache.offset;
+}
+
+/// finds a slot and a free page to fill or throws
+sfileno
+MemStore::reserveSapForWriting(Ipc::Mem::PageId &page)
+{
+    Ipc::Mem::PageId slot;
+    if (freeSlots->pop(slot)) {
+        debugs(20, 5, "got a previously free slot: " << slot);
+
+        if (Ipc::Mem::GetPage(Ipc::Mem::PageId::cachePage, page)) {
+            debugs(20, 5, "and got a previously free page: " << page);
+            return slot.number - 1;
+        } else {
+            debugs(20, 3, "but there is no free page, returning " << slot);
+            freeSlots->push(slot);
+        }
+    }
+
+    // catch free slots delivered to noteFreeMapSlice()
+    assert(!waitingFor);
+    waitingFor.slot = &slot;
+    waitingFor.page = &page;
+    if (map->purgeOne()) {
+        assert(!waitingFor); // noteFreeMapSlice() should have cleared it
+        assert(slot.set());
+        assert(page.set());
+        debugs(20, 5, "got previously busy " << slot << " and " << page);
+        return slot.number - 1;
+    }
+    assert(waitingFor.slot == &slot && waitingFor.page == &page);
+    waitingFor.slot = NULL;
+    waitingFor.page = NULL;
+
+    debugs(47, 3, "cannot get a slice; entries: " << map->entryCount());
+    throw TexcHere("ran out of mem-cache slots");
 }
 
-/// allocates map slot and calls copyToShm to store the entry in shared memory
 void
-MemStore::keep(StoreEntry &e)
+MemStore::noteFreeMapSlice(const Ipc::StoreMapSliceId sliceId)
 {
-    if (!map) {
-        debugs(20, 5, HERE << "No map to mem-cache " << e);
-        return;
+    Ipc::Mem::PageId &pageId = extras->items[sliceId].page;
+    debugs(20, 9, "slice " << sliceId << " freed " << pageId);
+    assert(pageId);
+    Ipc::Mem::PageId slotId;
+    slotId.pool = SpacePoolId;
+    slotId.number = sliceId + 1;
+    if (!waitingFor) {
+        // must zero pageId before we give slice (and pageId extras!) to others
+        Ipc::Mem::PutPage(pageId);
+        freeSlots->push(slotId);
+    } else {
+        *waitingFor.slot = slotId;
+        *waitingFor.page = pageId;
+        waitingFor.slot = NULL;
+        waitingFor.page = NULL;
+        pageId = Ipc::Mem::PageId();
     }
+}
 
-    sfileno index = 0;
-    Ipc::StoreMapSlot *slot = map->openForWriting(reinterpret_cast<const cache_key *>(e.key), index);
-    if (!slot) {
-        debugs(20, 5, HERE << "No room in mem-cache map to index " << e);
+void
+MemStore::write(StoreEntry &e)
+{
+    assert(e.mem_obj);
+
+    debugs(20, 7, "entry " << e);
+
+    switch (e.mem_obj->memCache.io) {
+    case MemObject::ioUndecided:
+        if (!shouldCache(e) || !startCaching(e)) {
+            e.mem_obj->memCache.io = MemObject::ioDone;
+            e.memOutDecision(false);
+            return;
+        }
+        break;
+
+    case MemObject::ioDone:
+    case MemObject::ioReading:
+        return; // we should not write in all of the above cases
+
+    case MemObject::ioWriting:
+        break; // already decided to write and still writing
+    }
+
+    try {
+        copyToShm(e);
+        if (e.store_status == STORE_OK) // done receiving new content
+            completeWriting(e);
+        else
+            CollapsedForwarding::Broadcast(e);
         return;
+    } catch (const std::exception &x) { // TODO: should we catch ... as well?
+        debugs(20, 2, "mem-caching error writing entry " << e << ": " << x.what());
+        // fall through to the error handling code
     }
 
-    MemStoreMap::Extras &extras = map->extras(index);
-    if (copyToShm(e, extras)) {
-        slot->set(e);
-        map->closeForWriting(index, false);
-    } else {
-        map->abortIo(index);
-    }
+    disconnect(e);
 }
 
-/// uses mem_hdr::copy() to copy local data to shared memory
-bool
-MemStore::copyToShm(StoreEntry &e, MemStoreMap::Extras &extras)
+void
+MemStore::completeWriting(StoreEntry &e)
 {
-    Ipc::Mem::PageId page;
-    if (!Ipc::Mem::GetPage(Ipc::Mem::PageId::cachePage, page)) {
-        debugs(20, 5, HERE << "No mem-cache page for " << e);
-        return false; // GetPage is responsible for any cleanup on failures
-    }
+    assert(e.mem_obj);
+    const int32_t index = e.mem_obj->memCache.index;
+    assert(index >= 0);
+    assert(map);
+
+    debugs(20, 5, "mem-cached all " << e.mem_obj->memCache.offset << " bytes of " << e);
+
+    e.mem_obj->memCache.index = -1;
+    e.mem_obj->memCache.io = MemObject::ioDone;
+    map->closeForWriting(index, false);
 
-    const int64_t bufSize = Ipc::Mem::PageSize();
-    const int64_t eSize = e.mem_obj->endOffset();
+    CollapsedForwarding::Broadcast(e); // before we close our transient entry!
+    Store::Root().transientsCompleteWriting(e);
+}
 
-    StoreIOBuffer sharedSpace(bufSize, 0,
-                              static_cast<char*>(PagePointer(page)));
+void
+MemStore::markForUnlink(StoreEntry &e)
+{
+    assert(e.mem_obj);
+    if (e.mem_obj->memCache.index >= 0)
+        map->freeEntry(e.mem_obj->memCache.index);
+}
 
-    // check that we kept everything or purge incomplete/sparse cached entry
-    const ssize_t copied = e.mem_obj->data_hdr.copy(sharedSpace);
-    if (eSize != copied) {
-        debugs(20, 2, HERE << "Failed to mem-cache " << e << ": " <<
-               eSize << "!=" << copied);
-        // cleanup
-        PutPage(page);
-        return false;
+void
+MemStore::unlink(StoreEntry &e)
+{
+    if (e.mem_obj && e.mem_obj->memCache.index >= 0) {
+        map->freeEntry(e.mem_obj->memCache.index);
+        disconnect(e);
+    } else if (map) {
+        // the entry may have been loaded and then disconnected from the cache
+        map->freeEntryByKey(reinterpret_cast<cache_key*>(e.key));
     }
 
-    debugs(20, 7, HERE << "mem-cached all " << eSize << " bytes of " << e <<
-           " in " << page);
-
-    theCurrentSize += Ipc::Mem::PageSize();
-    // remember storage location and size
-    extras.page = page;
-    extras.storedSize = copied;
-    return true;
+    e.destroyMemObject(); // XXX: but it may contain useful info such as a client list. The old code used to do that though, right?
 }
 
 void
-MemStore::cleanReadable(const sfileno fileno)
+MemStore::disconnect(StoreEntry &e)
 {
-    Ipc::Mem::PutPage(map->extras(fileno).page);
-    theCurrentSize -= Ipc::Mem::PageSize();
+    assert(e.mem_obj);
+    MemObject &mem_obj = *e.mem_obj;
+    if (mem_obj.memCache.index >= 0) {
+        if (mem_obj.memCache.io == MemObject::ioWriting) {
+            map->abortWriting(mem_obj.memCache.index);
+            mem_obj.memCache.index = -1;
+            mem_obj.memCache.io = MemObject::ioDone;
+            Store::Root().transientsAbandon(e); // broadcasts after the change
+        } else {
+            assert(mem_obj.memCache.io == MemObject::ioReading);
+            map->closeForReading(mem_obj.memCache.index);
+            mem_obj.memCache.index = -1;
+            mem_obj.memCache.io = MemObject::ioDone;
+        }
+    }
 }
 
 /// calculates maximum number of entries we need to store and map
 int64_t
 MemStore::EntryLimit()
 {
     if (!Config.memShared || !Config.memMaxSize)
         return 0; // no memory cache configured
 
-    const int64_t entrySize = Ipc::Mem::PageSize(); // for now
-    const int64_t entryLimit = Config.memMaxSize / entrySize;
+    const int64_t minEntrySize = Ipc::Mem::PageSize();
+    const int64_t entryLimit = Config.memMaxSize / minEntrySize;
     return entryLimit;
 }
 
-/// reports our needs for shared memory pages to Ipc::Mem::Pages
-class MemStoreClaimMemoryNeedsRr: public RegisteredRunner
+/// reports our needs for shared memory pages to Ipc::Mem::Pages;
+/// decides whether to use a shared memory cache or checks its configuration;
+/// and initializes shared memory segments used by MemStore
+class MemStoreRr: public Ipc::Mem::RegisteredRunner
 {
 public:
     /* RegisteredRunner API */
-    virtual void run(const RunnerRegistry &r);
+    MemStoreRr(): spaceOwner(NULL), mapOwner(NULL), extrasOwner(NULL) {}
+    virtual void finalizeConfig();
+    virtual void claimMemoryNeeds();
+    virtual void useConfig();
+    virtual ~MemStoreRr();
+
+protected:
+    /* Ipc::Mem::RegisteredRunner API */
+    virtual void create();
+
+private:
+    Ipc::Mem::Owner<Ipc::Mem::PageStack> *spaceOwner; ///< free slices Owner
+    MemStoreMap::Owner *mapOwner; ///< primary map Owner
+    Ipc::Mem::Owner<MemStoreMapExtras> *extrasOwner; ///< PageIds Owner
 };
 
-RunnerRegistrationEntry(rrClaimMemoryNeeds, MemStoreClaimMemoryNeedsRr);
+RunnerRegistrationEntry(MemStoreRr);
 
 void
-MemStoreClaimMemoryNeedsRr::run(const RunnerRegistry &)
+MemStoreRr::claimMemoryNeeds()
 {
     Ipc::Mem::NotePageNeed(Ipc::Mem::PageId::cachePage, MemStore::EntryLimit());
 }
 
-/// decides whether to use a shared memory cache or checks its configuration
-class MemStoreCfgRr: public ::RegisteredRunner
-{
-public:
-    /* RegisteredRunner API */
-    virtual void run(const RunnerRegistry &);
-};
-
-RunnerRegistrationEntry(rrFinalizeConfig, MemStoreCfgRr);
-
-void MemStoreCfgRr::run(const RunnerRegistry &r)
+void
+MemStoreRr::finalizeConfig()
 {
     // decide whether to use a shared memory cache if the user did not specify
     if (!Config.memShared.configured()) {
         Config.memShared.configure(Ipc::Atomic::Enabled() &&
                                    Ipc::Mem::Segment::Enabled() && UsingSmp() &&
                                    Config.memMaxSize > 0);
