         fatal("Unknown icon format while reading mime.conf\n");
 
     StoreEntry::getPublic(this, url_, Http::METHOD_GET);
 }
 
 void
-MimeIcon::created (StoreEntry *newEntry)
+MimeIcon::created(StoreEntry *newEntry)
 {
     /* if the icon is already in the store, do nothing */
     if (!newEntry->isNull())
         return;
+    // XXX: if a 204 is cached due to earlier load 'failure' we should try to reload.
 
-    int fd;
-    int n;
-    RequestFlags flags;
-    struct stat sb;
-    LOCAL_ARRAY(char, path, MAXPATHLEN);
-    char *buf;
-
-    snprintf(path, MAXPATHLEN, "%s/%s", Config.icons.directory, icon_);
+    // default is a 200 object with image data.
+    // set to the backup value of 204 on image loading errors
+    Http::StatusCode status = Http::scOkay;
+
+    static char path[MAXPATHLEN];
+    *path = 0;
+    if (snprintf(path, sizeof(path)-1, "%s/%s", Config.icons.directory, icon_) < 0) {
+        debugs(25, DBG_CRITICAL, "ERROR: icon file '" << Config.icons.directory << "/" << icon_ << "' path is longer than " << MAXPATHLEN << " bytes");
+        status = Http::scNoContent;
+    }
 
-    fd = file_open(path, O_RDONLY | O_BINARY);
-    if (fd < 0) {
-        debugs(25, DBG_CRITICAL, "Problem opening icon file " << path << ": " << xstrerror());
-        return;
+    int fd = -1;
+    errno = 0;
+    if (status == Http::scOkay && (fd = file_open(path, O_RDONLY | O_BINARY)) < 0) {
+        int xerrno = errno;
+        debugs(25, DBG_CRITICAL, "ERROR: opening icon file " << path << ": " << xstrerr(xerrno));
+        status = Http::scNoContent;
     }
-    if (fstat(fd, &sb) < 0) {
-        debugs(25, DBG_CRITICAL, "Problem opening icon file. Fd: " << fd << ", fstat error " << xstrerror());
+
+    struct stat sb;
+    errno = 0;
+    if (status == Http::scOkay && fstat(fd, &sb) < 0) {
+        int xerrno = errno;
+        debugs(25, DBG_CRITICAL, "ERROR: opening icon file " << path << " FD " << fd << ", fstat error " << xstrerr(xerrno));
         file_close(fd);
-        return;
+        status = Http::scNoContent;
     }
 
+    // fill newEntry with a canned 2xx response object
+    RequestFlags flags;
     flags.cachable = true;
     StoreEntry *e = storeCreateEntry(url_,url_,flags,Http::METHOD_GET);
     assert(e != NULL);
     EBIT_SET(e->flags, ENTRY_SPECIAL);
     e->setPublicKey();
     e->buffer();
     HttpRequest *r = HttpRequest::CreateFromUrl(url_);
 
     if (NULL == r)
-        fatal("mimeLoadIcon: cannot parse internal URL");
+        fatalf("mimeLoadIcon: cannot parse internal URL: %s", url_);
 
     e->mem_obj->request = r;
     HTTPMSGLOCK(e->mem_obj->request);
 
     HttpReply *reply = new HttpReply;
 
-    reply->setHeaders(Http::scOkay, NULL, mimeGetContentType(icon_), sb.st_size, sb.st_mtime, -1);
+    if (status == Http::scNoContent)
+        reply->setHeaders(status, NULL, NULL, 0, -1, -1);
+    else
+        reply->setHeaders(status, NULL, mimeGetContentType(icon_), sb.st_size, sb.st_mtime, -1);
     reply->cache_control = new HttpHdrCc();
     reply->cache_control->maxAge(86400);
     reply->header.putCc(reply->cache_control);
     e->replaceHttpReply(reply);
 
-    /* read the file into the buffer and append it to store */
-    buf = (char *)memAllocate(MEM_4K_BUF);
-    while ((n = FD_READ_METHOD(fd, buf, 4096)) > 0)
-        e->append(buf, n);
+    if (status == Http::scOkay) {
+        /* read the file into the buffer and append it to store */
+        int n;
+        char *buf = (char *)memAllocate(MEM_4K_BUF);
+        while ((n = FD_READ_METHOD(fd, buf, 4096)) > 0)
+            e->append(buf, n);
+
+        file_close(fd);
+        memFree(buf, MEM_4K_BUF);
+    }
 
-    file_close(fd);
     e->flush();
     e->complete();
     e->timestampsSet();
-    e->unlock();
-    memFree(buf, MEM_4K_BUF);
+    e->unlock("MimeIcon::created");
     debugs(25, 3, "Loaded icon " << url_);
 }
 
 MimeEntry::~MimeEntry()
 {
     xfree(pattern);
