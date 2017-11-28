     // We do not lock e because we do not want to prevent its destruction;
     // e is tied to us via mem_obj so we will know when it is destructed.
     locals->at(index) = e;
     return e;
 }
 
-void
-Transients::get(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
-{
-    // XXX: not needed but Store parent forces us to implement this
-    fatal("Transients::get(key,callback,data) should not be called");
-}
-
 StoreEntry *
 Transients::findCollapsed(const sfileno index)
 {
     if (!map)
         return NULL;
 
