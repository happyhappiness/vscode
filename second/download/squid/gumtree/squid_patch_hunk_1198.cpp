 /*
  * local variables
  */
 static std::stack<StoreEntry*> LateReleaseStack;
 MemAllocator *StoreEntry::pool = NULL;
 
-StorePointer Store::CurrentRoot = NULL;
-
-void
-Store::Root(Store * aRoot)
-{
-    CurrentRoot = aRoot;
-}
-
-void
-Store::Root(StorePointer aRoot)
-{
-    Root(aRoot.getRaw());
-}
-
 void
 Store::Stats(StoreEntry * output)
 {
-    assert (output);
+    assert(output);
     Root().stat(*output);
 }
 
-void
-Store::create()
-{}
-
-void
-Store::diskFull()
-{}
-
-void
-Store::sync()
-{}
-
-void
-Store::unlink (StoreEntry &anEntry)
-{
-    fatal("Store::unlink on invalid Store\n");
-}
-
+// XXX: new/delete operators need to be replaced with MEMPROXY_CLASS
+// definitions but doing so exposes bug 4370, and maybe 4354 and 4355
 void *
 StoreEntry::operator new (size_t bytecount)
 {
-    assert (bytecount == sizeof (StoreEntry));
+    assert(bytecount == sizeof (StoreEntry));
 
     if (!pool) {
         pool = memPoolCreate ("StoreEntry", bytecount);
     }
 
     return pool->alloc();
