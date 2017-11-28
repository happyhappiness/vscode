         args = args->next;
     }
 
     storeAppendPrintf(entry, "\n");
 }
 
-void
-YesNoNone::configure(bool beSet)
-{
-    option = beSet ? +1 : -1;
-}
-
-YesNoNone::operator void*() const
-{
-    assert(option != 0); // must call configure() first
-    return option > 0 ? (void*)this : NULL;
-}
-
-
 inline void
 free_YesNoNone(YesNoNone *)
 {
     // do nothing: no explicit cleanup is required
 }
 
