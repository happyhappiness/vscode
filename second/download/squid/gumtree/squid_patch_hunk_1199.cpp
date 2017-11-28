         /* Create "vary" base object */
         String vary;
         StoreEntry *pe = storeCreateEntry(mem_obj->storeId(), mem_obj->logUri(), request->flags, request->method);
         /* We are allowed to do this typecast */
         HttpReply *rep = new HttpReply;
         rep->setHeaders(Http::scOkay, "Internal marker object", "x-squid-internal/vary", -1, -1, squid_curtime + 100000);
-        vary = mem_obj->getReply()->header.getList(HDR_VARY);
+        vary = mem_obj->getReply()->header.getList(Http::HdrType::VARY);
 
         if (vary.size()) {
             /* Again, we own this structure layout */
-            rep->header.putStr(HDR_VARY, vary.termedBuf());
+            rep->header.putStr(Http::HdrType::VARY, vary.termedBuf());
             vary.clean();
         }
 
 #if X_ACCELERATOR_VARY
-        vary = mem_obj->getReply()->header.getList(HDR_X_ACCELERATOR_VARY);
+        vary = mem_obj->getReply()->header.getList(Http::HdrType::HDR_X_ACCELERATOR_VARY);
 
         if (vary.size() > 0) {
             /* Again, we own this structure layout */
-            rep->header.putStr(HDR_X_ACCELERATOR_VARY, vary.termedBuf());
+            rep->header.putStr(Http::HdrType::HDR_X_ACCELERATOR_VARY, vary.termedBuf());
             vary.clean();
         }
 
 #endif
         pe->replaceHttpReply(rep, false); // no write until key is public
 
