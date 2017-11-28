 
 /// adds slot to the free slot index
 void
 Rock::Rebuild::freeSlot(const SlotId slotId, const bool invalid)
 {
     debugs(47,5, sd->index << " frees slot " << slotId);
-    LoadingEntry &le = entries[slotId];
-    assert(!le.freed);
-    le.freed = 1;
+    LoadingSlot slot = loadingSlot(slotId);
+    assert(!slot.freed());
+    slot.freed(true);
 
     if (invalid) {
         ++counts.invalid;
         //sd->unlink(fileno); leave garbage on disk, it should not hurt
     }
 
     Ipc::Mem::PageId pageId;
     pageId.pool = sd->index+1;
     pageId.number = slotId+1;
     sd->freeSlots->push(pageId);
 }
 
-/// adds slot to the free slot index but only if the slot is unused
+/// freeSlot() for never-been-mapped slots
 void
-Rock::Rebuild::freeSlotIfIdle(const SlotId slotId, const bool invalid)
+Rock::Rebuild::freeUnusedSlot(const SlotId slotId, const bool invalid)
 {
-    const LoadingEntry &le = entries[slotId];
-
+    LoadingSlot slot = loadingSlot(slotId);
     // mapped slots must be freed via freeBadEntry() to keep the map in sync
-    assert(!le.mapped);
-
-    if (!le.used())
-        freeSlot(slotId, invalid);
+    assert(!slot.mapped());
+    freeSlot(slotId, invalid);
 }
 
 /// adds slot to the entry chain in the map
 void
 Rock::Rebuild::mapSlot(const SlotId slotId, const DbCellHeader &header)
 {
-    LoadingEntry &le = entries[slotId];
-    assert(!le.mapped);
-    assert(!le.freed);
-    le.mapped = 1;
+    LoadingSlot slot = loadingSlot(slotId);
+    assert(!slot.mapped());
+    assert(!slot.freed());
+    slot.mapped(true);
 
     Ipc::StoreMapSlice slice;
     slice.next = header.nextSlot;
     slice.size = header.payloadSize;
     sd->map->importSlice(slotId, slice);
 }
 
+template <class SlotIdType> // accommodates atomic and simple SlotIds.
+void
+Rock::Rebuild::chainSlots(SlotIdType &from, const SlotId to)
+{
+    LoadingSlot slot = loadingSlot(to);
+    assert(slot.more < 0);
+    slot.more = from; // may still be unset
+    from = to;
+}
+
 /// adds slot to an existing entry chain; caller must check that the slot
 /// belongs to the chain it is being added to
 void
 Rock::Rebuild::addSlotToEntry(const sfileno fileno, const SlotId slotId, const DbCellHeader &header)
 {
-    LoadingEntry &le = entries[fileno];
+    LoadingEntry le = loadingEntry(fileno);
     Ipc::StoreMapAnchor &anchor = sd->map->writeableEntry(fileno);
 
-    assert(le.version == header.version);
-
-    // mark anchor as loaded or add the secondary slot to the chain
-    LoadingEntry &inode = entries[header.firstSlot];
-    if (header.firstSlot == slotId) {
-        debugs(47,5, "adding inode");
-        assert(!inode.freed);
-        le.anchored = 1;
+    debugs(47,9, "adding " << slotId << " to entry " << fileno);
+    // we do not need to preserve the order
+    if (le.anchored()) {
+        LoadingSlot inode = loadingSlot(anchor.start);
+        chainSlots(inode.more, slotId);
     } else {
-        debugs(47,9, "linking " << slotId << " to " << inode.more);
-        // we do not need to preserve the order
-        LoadingEntry &slice = entries[slotId];
-        assert(!slice.freed);
-        assert(slice.more < 0);
-        slice.more = inode.more;
-        inode.more = slotId;
+        chainSlots(anchor.start, slotId);
     }
 
-    if (header.firstSlot == slotId && !importEntry(anchor, fileno, header)) {
-        le.state = LoadingEntry::leCorrupted;
-        freeBadEntry(fileno, "corrupted metainfo");
-        return;
-    }
+    le.size += header.payloadSize; // must precede freeBadEntry() calls
 
-    // set total entry size and/or check it for consistency
-    debugs(47, 8, "header.entrySize: " << header.entrySize << " swap_file_sz: " << anchor.basics.swap_file_sz);
-    uint64_t totalSize = header.entrySize;
-    assert(totalSize != static_cast<uint64_t>(-1));
-    if (!totalSize && anchor.basics.swap_file_sz) {
-        assert(anchor.basics.swap_file_sz != static_cast<uint64_t>(-1));
-        // perhaps we loaded a later slot (with entrySize) earlier
-        totalSize = anchor.basics.swap_file_sz;
-    } else if (totalSize && !anchor.basics.swap_file_sz) {
-        anchor.basics.swap_file_sz = totalSize;
-        assert(anchor.basics.swap_file_sz != static_cast<uint64_t>(-1));
-    } else if (totalSize != anchor.basics.swap_file_sz) {
-        le.state = LoadingEntry::leCorrupted;
-        freeBadEntry(fileno, "size mismatch");
-        return;
+    if (header.firstSlot == slotId) {
+        debugs(47,5, "added inode");
+
+        if (le.anchored()) { // we have already added another inode slot
+            freeBadEntry(fileno, "inode conflict");
+            ++counts.clashcount;
+            return;
+        }
+
+        le.anchored(true);
+
+        if (!importEntry(anchor, fileno, header)) {
+            freeBadEntry(fileno, "corrupted metainfo");
+            return;
+        }
+
+        // set total entry size and/or check it for consistency
+        if (const uint64_t totalSize = header.entrySize) {
+            assert(totalSize != static_cast<uint64_t>(-1));
+            if (!anchor.basics.swap_file_sz) {
+                anchor.basics.swap_file_sz = totalSize;
+                assert(anchor.basics.swap_file_sz != static_cast<uint64_t>(-1));
+            } else if (totalSize != anchor.basics.swap_file_sz) {
+                freeBadEntry(fileno, "size mismatch");
+                return;
+            }
+        }
     }
 
-    le.size += header.payloadSize;
+    const uint64_t totalSize = anchor.basics.swap_file_sz; // may be 0/unknown
 
     if (totalSize > 0 && le.size > totalSize) { // overflow
         debugs(47, 8, "overflow: " << le.size << " > " << totalSize);
-        le.state = LoadingEntry::leCorrupted;
         freeBadEntry(fileno, "overflowing");
         return;
     }
 
     mapSlot(slotId, header);
-    if (totalSize > 0 && le.size == totalSize) {
-        // entry fully loaded, unlock it
-        // we have validated that all db cells for this entry were loaded
-        EBIT_SET(anchor.basics.flags, ENTRY_VALIDATED);
-        le.state = LoadingEntry::leLoaded;
-        sd->map->closeForWriting(fileno, false);
-        ++counts.objcount;
-    }
+    if (totalSize > 0 && le.size == totalSize)
+        finalizeOrFree(fileno, le); // entry is probably fully loaded now
 }
 
 /// initialize housekeeping information for a newly accepted entry
 void
 Rock::Rebuild::primeNewEntry(Ipc::StoreMap::Anchor &anchor, const sfileno fileno, const DbCellHeader &header)
 {
     anchor.setKey(reinterpret_cast<const cache_key*>(header.key));
     assert(header.firstSlot >= 0);
-    anchor.start = header.firstSlot;
+    anchor.start = -1; // addSlotToEntry() will set it
 
     assert(anchor.basics.swap_file_sz != static_cast<uint64_t>(-1));
 
-    LoadingEntry &le = entries[fileno];
-    le.state = LoadingEntry::leLoading;
+    LoadingEntry le = loadingEntry(fileno);
+    le.state(LoadingEntry::leLoading);
     le.version = header.version;
     le.size = 0;
 }
 
 /// handle a slot from an entry that we have not seen before
 void
 Rock::Rebuild::startNewEntry(const sfileno fileno, const SlotId slotId, const DbCellHeader &header)
 {
-    // If some other from-disk entry is/was using this slot as its inode OR
-    // if some other from-disk entry is/was using our inode slot, then the
-    // entries are conflicting. We cannot identify other entries, so we just
-    // remove ours and hope that the others were/will be handled correctly.
-    const LoadingEntry &slice = entries[slotId];
-    const LoadingEntry &inode = entries[header.firstSlot];
-    if (slice.used() || inode.used()) {
-        debugs(47,8, "slice/inode used: " << slice.used() << inode.used());
-        LoadingEntry &le = entries[fileno];
-        le.state = LoadingEntry::leCorrupted;
-        freeSlotIfIdle(slotId, slotId == header.firstSlot);
-        // if not idle, the other entry will handle its slice
-        ++counts.clashcount;
-        return;
-    }
-
     // A miss may have been stored at our fileno while we were loading other
     // slots from disk. We ought to preserve that entry because it is fresher.
     const bool overwriteExisting = false;
     if (Ipc::StoreMap::Anchor *anchor = sd->map->openForWritingAt(fileno, overwriteExisting)) {
         primeNewEntry(*anchor, fileno, header);
         addSlotToEntry(fileno, slotId, header); // may fail
         assert(anchor->basics.swap_file_sz != static_cast<uint64_t>(-1));
     } else {
         // A new from-network entry is occupying our map slot; let it be, but
         // save us from the trouble of going through the above motions again.
-        LoadingEntry &le = entries[fileno];
-        le.state = LoadingEntry::leIgnored;
-        freeSlotIfIdle(slotId, false);
+        LoadingEntry le = loadingEntry(fileno);
+        le.state(LoadingEntry::leIgnored);
+        freeUnusedSlot(slotId, false);
     }
 }
 
 /// does the header belong to the fileno entry being loaded?
 bool
 Rock::Rebuild::sameEntry(const sfileno fileno, const DbCellHeader &header) const
 {
+    // Header updates always result in multi-start chains and often
+    // result in multi-version chains so we can only compare the keys.
     const Ipc::StoreMap::Anchor &anchor = sd->map->writeableEntry(fileno);
-    const LoadingEntry &le = entries[fileno];
-    // any order will work, but do fast comparisons first:
-    return le.version == header.version &&
-           anchor.start == static_cast<Ipc::StoreMapSliceId>(header.firstSlot) &&
-           anchor.sameKey(reinterpret_cast<const cache_key*>(header.key));
-}
-
-/// is the new header consistent with information already loaded?
-bool
-Rock::Rebuild::canAdd(const sfileno fileno, const SlotId slotId, const DbCellHeader &header) const
-{
-    if (!sameEntry(fileno, header)) {
-        debugs(79, 7, "cannot add; wrong entry");
-        return false;
-    }
-
-    const LoadingEntry &le = entries[slotId];
-    // We cannot add a slot that was already declared free or mapped.
-    if (le.freed || le.mapped) {
-        debugs(79, 7, "cannot add; freed/mapped: " << le.freed << le.mapped);
-        return false;
-    }
-
-    if (slotId == header.firstSlot) {
-        // If we are the inode, the anchored flag cannot be set yet.
-        if (entries[fileno].anchored) {
-            debugs(79, 7, "cannot add; extra anchor");
-            return false;
-        }
-
-        // And there should have been some other slot for this entry to exist.
-        if (le.more < 0) {
-            debugs(79, 7, "cannot add; missing slots");
-            return false;
-        }
-
-        return true;
-    }
-
-    // We are the continuation slice so the more field is reserved for us.
-    if (le.more >= 0) {
-        debugs(79, 7, "cannot add; foreign slot");
-        return false;
-    }
-
-    return true;
+    return anchor.sameKey(reinterpret_cast<const cache_key*>(header.key));
 }
 
 /// handle freshly loaded (and validated) db slot header
 void
 Rock::Rebuild::useNewSlot(const SlotId slotId, const DbCellHeader &header)
 {
-    LoadingEntry &slice = entries[slotId];
-    assert(!slice.freed); // we cannot free what was not loaded
-
     const cache_key *const key =
         reinterpret_cast<const cache_key*>(header.key);
-    const sfileno fileno = sd->map->anchorIndexByKey(key);
+    const sfileno fileno = sd->map->fileNoByKey(key);
     assert(0 <= fileno && fileno < dbEntryLimit);
 
-    LoadingEntry &le = entries[fileno];
-    debugs(47,9, "entry " << fileno << " state: " << le.state << ", inode: " <<
+    LoadingEntry le = loadingEntry(fileno);
+    debugs(47,9, "entry " << fileno << " state: " << le.state() << ", inode: " <<
            header.firstSlot << ", size: " << header.payloadSize);
 
-    switch (le.state) {
+    switch (le.state()) {
 
     case LoadingEntry::leEmpty: {
         startNewEntry(fileno, slotId, header);
         break;
     }
 
     case LoadingEntry::leLoading: {
-        if (canAdd(fileno, slotId, header)) {
-            addSlotToEntry(fileno, slotId, header);
+        if (sameEntry(fileno, header)) {
+            addSlotToEntry(fileno, slotId, header); // may fail
         } else {
             // either the loading chain or this slot is stale;
             // be conservative and ignore both (and any future ones)
-            le.state = LoadingEntry::leCorrupted;
             freeBadEntry(fileno, "duplicated");
-            freeSlotIfIdle(slotId, slotId == header.firstSlot);
+            freeUnusedSlot(slotId, true);
             ++counts.dupcount;
         }
         break;
     }
 
     case LoadingEntry::leLoaded: {
         // either the previously loaded chain or this slot is stale;
         // be conservative and ignore both (and any future ones)
-        le.state = LoadingEntry::leCorrupted;
+        le.state(LoadingEntry::leCorrupted);
         sd->map->freeEntry(fileno); // may not be immediately successful
-        freeSlotIfIdle(slotId, slotId == header.firstSlot);
+        freeUnusedSlot(slotId, true);
         ++counts.dupcount;
         break;
     }
 
     case LoadingEntry::leCorrupted: {
         // previously seen slots messed things up so we must ignore this one
-        freeSlotIfIdle(slotId, false);
+        freeUnusedSlot(slotId, true);
         break;
     }
 
     case LoadingEntry::leIgnored: {
         // already replaced by a fresher or colliding from-network entry
-        freeSlotIfIdle(slotId, false);
+        freeUnusedSlot(slotId, false);
         break;
     }
     }
 }
 
