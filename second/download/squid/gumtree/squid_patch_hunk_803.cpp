         storeAppendPrintf(&e, " READ-ONLY");
 
     storeAppendPrintf(&e, "\n");
 
 }
 
+SBuf
+Rock::SwapDir::inodeMapPath() const
+{
+    return Ipc::Mem::Segment::Name(SBuf(path), "map");
+}
+
+const char *
+Rock::SwapDir::freeSlotsPath() const
+{
+    static String spacesPath;
+    spacesPath = path;
+    spacesPath.append("_spaces");
+    return spacesPath.termedBuf();
+}
+
 namespace Rock
 {
-RunnerRegistrationEntry(rrAfterConfig, SwapDirRr);
+RunnerRegistrationEntry(SwapDirRr);
 }
 
-void Rock::SwapDirRr::create(const RunnerRegistry &)
+void Rock::SwapDirRr::create()
 {
-    Must(owners.empty());
+    Must(mapOwners.empty() && freeSlotsOwners.empty());
     for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
         if (const Rock::SwapDir *const sd = dynamic_cast<Rock::SwapDir *>(INDEXSD(i))) {
-            Rock::SwapDir::DirMap::Owner *const owner =
-                Rock::SwapDir::DirMap::Init(sd->path, sd->entryLimitAllowed());
-            owners.push_back(owner);
+            const int64_t capacity = sd->slotLimitActual();
+
+            SwapDir::DirMap::Owner *const mapOwner =
+                SwapDir::DirMap::Init(sd->inodeMapPath(), capacity);
+            mapOwners.push_back(mapOwner);
+
+            // TODO: somehow remove pool id and counters from PageStack?
+            Ipc::Mem::Owner<Ipc::Mem::PageStack> *const freeSlotsOwner =
+                shm_new(Ipc::Mem::PageStack)(sd->freeSlotsPath(),
+                                             i+1, capacity, 0);
+            freeSlotsOwners.push_back(freeSlotsOwner);
+
+            // TODO: add method to initialize PageStack with no free pages
+            while (true) {
+                Ipc::Mem::PageId pageId;
+                if (!freeSlotsOwner->object()->pop(pageId))
+                    break;
+            }
         }
     }
 }
 
 Rock::SwapDirRr::~SwapDirRr()
 {
-    for (size_t i = 0; i < owners.size(); ++i)
-        delete owners[i];
+    for (size_t i = 0; i < mapOwners.size(); ++i) {
+        delete mapOwners[i];
+        delete freeSlotsOwners[i];
+    }
 }
+
