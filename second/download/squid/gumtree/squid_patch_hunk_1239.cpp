     flags.cachable = true;
     StoreEntry *e = storeCreateEntry(url_,url_,flags,Http::METHOD_GET);
     assert(e != NULL);
     EBIT_SET(e->flags, ENTRY_SPECIAL);
     e->setPublicKey();
     e->buffer();
-    HttpRequest *r = HttpRequest::CreateFromUrl(url_);
+    const MasterXaction::Pointer mx = new MasterXaction(XactionInitiator::initIcon);
+    HttpRequest *r = HttpRequest::FromUrl(url_, mx);
 
     if (NULL == r)
         fatalf("mimeLoadIcon: cannot parse internal URL: %s", url_);
 
     e->mem_obj->request = r;
     HTTPMSGLOCK(e->mem_obj->request);
