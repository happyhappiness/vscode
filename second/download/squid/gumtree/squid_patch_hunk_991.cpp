 static void dump_HeaderWithAclList(StoreEntry * entry, const char *name, HeaderWithAclList *headers)
 {
     if (!headers)
         return;
 
     for (HeaderWithAclList::iterator hwa = headers->begin(); hwa != headers->end(); ++hwa) {
-        storeAppendPrintf(entry, "%s ", hwa->fieldName.c_str());
-        storeAppendPrintf(entry, "%s ", hwa->fieldValue.c_str());
+        storeAppendPrintf(entry, "%s %s %s", name, hwa->fieldName.c_str(), hwa->fieldValue.c_str());
         if (hwa->aclList)
             dump_acl_list(entry, hwa->aclList);
         storeAppendPrintf(entry, "\n");
     }
 }
 
