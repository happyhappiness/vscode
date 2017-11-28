 Rock::SwapDir::dumpRateOption(StoreEntry * e) const
 {
     if (fileConfig.ioRate >= 0)
         storeAppendPrintf(e, " max-swap-rate=%d", fileConfig.ioRate);
 }
 
+/// parses size-specific options; mimics ::SwapDir::optionObjectSizeParse()
+bool
+Rock::SwapDir::parseSizeOption(char const *option, const char *value, int reconfig)
+{
+    uint64_t *storedSize;
+    if (strcmp(option, "slot-size") == 0)
+        storedSize = &slotSize;
+    else
+        return false;
+
+    if (!value)
+        self_destruct();
+
+    // TODO: handle size units and detect parsing errors better
+    const uint64_t newSize = strtoll(value, NULL, 10);
+    if (newSize <= 0) {
+        debugs(3, DBG_CRITICAL, "FATAL: cache_dir " << path << ' ' << option << " must be positive; got: " << newSize);
+        self_destruct();
+    }
+
+    if (newSize <= sizeof(DbCellHeader)) {
+        debugs(3, DBG_CRITICAL, "FATAL: cache_dir " << path << ' ' << option << " must exceed " << sizeof(DbCellHeader) << "; got: " << newSize);
+        self_destruct();
+    }
+
+    if (!reconfig)
+        *storedSize = newSize;
+    else if (*storedSize != newSize) {
+        debugs(3, DBG_IMPORTANT, "WARNING: cache_dir " << path << ' ' << option
+               << " cannot be changed dynamically, value left unchanged: " <<
+               *storedSize);
+    }
+
+    return true;
+}
+
+/// reports size-specific options; mimics ::SwapDir::optionObjectSizeDump()
+void
+Rock::SwapDir::dumpSizeOption(StoreEntry * e) const
+{
+    storeAppendPrintf(e, " slot-size=%" PRId64, slotSize);
+}
+
 /// check the results of the configuration; only level-0 debugging works here
 void
 Rock::SwapDir::validateOptions()
 {
-    if (max_objsize <= 0)
-        fatal("Rock store requires a positive max-size");
+    if (slotSize <= 0)
+        fatal("Rock store requires a positive slot-size");
 
     const int64_t maxSizeRoundingWaste = 1024 * 1024; // size is configured in MB
-    const int64_t maxObjectSizeRoundingWaste = maxObjectSize();
+    const int64_t slotSizeRoundingWaste = slotSize;
     const int64_t maxRoundingWaste =
-        max(maxSizeRoundingWaste, maxObjectSizeRoundingWaste);
-    const int64_t usableDiskSize = diskOffset(entryLimitAllowed());
-    const int64_t diskWasteSize = maxSize() - usableDiskSize;
-    Must(diskWasteSize >= 0);
-
-    // warn if maximum db size is not reachable due to sfileno limit
-    if (entryLimitAllowed() == entryLimitHigh() &&
-            diskWasteSize >= maxRoundingWaste) {
-        debugs(47, DBG_CRITICAL, "Rock store cache_dir[" << index << "] '" << path << "':");
-        debugs(47, DBG_CRITICAL, "\tmaximum number of entries: " << entryLimitAllowed());
-        debugs(47, DBG_CRITICAL, "\tmaximum object size: " << maxObjectSize() << " Bytes");
-        debugs(47, DBG_CRITICAL, "\tmaximum db size: " << maxSize() << " Bytes");
-        debugs(47, DBG_CRITICAL, "\tusable db size:  " << usableDiskSize << " Bytes");
-        debugs(47, DBG_CRITICAL, "\tdisk space waste: " << diskWasteSize << " Bytes");
-        debugs(47, DBG_CRITICAL, "WARNING: Rock store config wastes space.");
+        max(maxSizeRoundingWaste, slotSizeRoundingWaste);
+
+    // an entry consumes at least one slot; round up to reduce false warnings
+    const int64_t blockSize = static_cast<int64_t>(slotSize);
+    const int64_t maxObjSize = max(blockSize,
+                                   ((maxObjectSize()+blockSize-1)/blockSize)*blockSize);
+
+    // Does the "sfileno*max-size" limit match configured db capacity?
+    const double entriesMayOccupy = entryLimitAbsolute()*static_cast<double>(maxObjSize);
+    if (entriesMayOccupy + maxRoundingWaste < maxSize()) {
+        const int64_t diskWasteSize = maxSize() - static_cast<int64_t>(entriesMayOccupy);
+        debugs(47, DBG_CRITICAL, "WARNING: Rock cache_dir " << path << " wastes disk space due to entry limits:" <<
+               "\n\tconfigured db capacity: " << maxSize() << " bytes" <<
+               "\n\tconfigured db slot size: " << slotSize << " bytes" <<
+               "\n\tconfigured maximum entry size: " << maxObjectSize() << " bytes" <<
+               "\n\tmaximum number of cache_dir entries supported by Squid: " << entryLimitAbsolute() <<
+               "\n\tdisk space all entries may use: " << entriesMayOccupy << " bytes" <<
+               "\n\tdisk space wasted: " << diskWasteSize << " bytes");
+    }
+
+    // Does the "absolute slot count" limit match configured db capacity?
+    const double slotsMayOccupy = slotLimitAbsolute()*static_cast<double>(slotSize);
+    if (slotsMayOccupy + maxRoundingWaste < maxSize()) {
+        const int64_t diskWasteSize = maxSize() - static_cast<int64_t>(entriesMayOccupy);
+        debugs(47, DBG_CRITICAL, "WARNING: Rock cache_dir " << path << " wastes disk space due to slot limits:" <<
+               "\n\tconfigured db capacity: " << maxSize() << " bytes" <<
+               "\n\tconfigured db slot size: " << slotSize << " bytes" <<
+               "\n\tmaximum number of rock cache_dir slots supported by Squid: " << slotLimitAbsolute() <<
+               "\n\tdisk space all slots may use: " << slotsMayOccupy << " bytes" <<
+               "\n\tdisk space wasted: " << diskWasteSize << " bytes");
     }
 }
 
 void
 Rock::SwapDir::rebuild()
 {
     //++StoreController::store_dirs_rebuilding; // see Rock::SwapDir::init()
     AsyncJob::Start(new Rebuild(this));
 }
 
-/* Add a new object to the cache with empty memory copy and pointer to disk
- * use to rebuild store from disk. Based on UFSSwapDir::addDiskRestore */
-bool
-Rock::SwapDir::addEntry(const int filen, const DbCellHeader &header, const StoreEntry &from)
-{
-    debugs(47, 8, HERE << &from << ' ' << from.getMD5Text() <<
-           ", filen="<< std::setfill('0') << std::hex << std::uppercase <<
-           std::setw(8) << filen);
-
-    sfileno newLocation = 0;
-    if (Ipc::StoreMapSlot *slot = map->openForWriting(reinterpret_cast<const cache_key *>(from.key), newLocation)) {
-        if (filen == newLocation) {
-            slot->set(from);
-            map->extras(filen) = header;
-        } // else some other, newer entry got into our cell
-        map->closeForWriting(newLocation, false);
-        return filen == newLocation;
-    }
-
-    return false;
-}
-
 bool
 Rock::SwapDir::canStore(const StoreEntry &e, int64_t diskSpaceNeeded, int &load) const
 {
     if (!::SwapDir::canStore(e, sizeof(DbCellHeader)+diskSpaceNeeded, load))
         return false;
 
