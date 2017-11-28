 
     storeAppendPrintf(entry, "\n");
 }
 
 inline void
 free_YesNoNone(YesNoNone *)
-{
-    // do nothing: no explicit cleanup is required
-}
+{}
 
 static void
 parse_YesNoNone(YesNoNone *option)
 {
     int value = 0;
     parse_onoff(&value);
