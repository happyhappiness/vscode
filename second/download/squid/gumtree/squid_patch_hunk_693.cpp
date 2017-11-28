 
 ACLASN::match(Ip::Address toMatch)
 {
     return asnMatchIp(data, toMatch);
 }
 
-wordlist *
-ACLASN::dump()
+SBufList
+ACLASN::dump() const
 {
-    wordlist *W = NULL;
-    char buf[32];
+    SBufList sl;
+
     CbDataList<int> *ldata = data;
 
     while (ldata != NULL) {
-        snprintf(buf, sizeof(buf), "%d", ldata->element);
-        wordlistAdd(&W, buf);
+        SBuf s;
+        s.Printf("%d", ldata->element);
+        sl.push_back(s);
         ldata = ldata->next;
     }
 
-    return W;
+    return sl;
 }
 
 bool
 ACLASN::empty () const
 {
     return data == NULL;
