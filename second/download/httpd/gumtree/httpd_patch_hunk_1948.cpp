 
     /* process remaining entries oldest to newest, the check for an emtpy
      * ring actually isn't necessary except when the compiler does
      * corrupt 64bit arithmetics which happend to me once, so better safe
      * than sorry
      */
-    while (sum > max && !interrupted && !APR_RING_EMPTY(&root, _entry, link)) {
+    while (s.sum > s.max && !interrupted
+           && !APR_RING_EMPTY(&root, _entry, link)) {
         oldest = APR_RING_FIRST(&root);
 
         for (e = APR_RING_NEXT(oldest, link);
              e != APR_RING_SENTINEL(&root, _entry, link);
              e = APR_RING_NEXT(e, link)) {
             if (e->dtime < oldest->dtime) {
                 oldest = e;
             }
         }
 
         delete_entry(path, oldest->basename, pool);
-        sum -= oldest->hsize;
-        sum -= oldest->dsize;
-        entries--;
+        s.sum -= oldest->hsize;
+        s.sum -= oldest->dsize;
+        s.entries--;
+        s.dfresh++;
         APR_RING_REMOVE(oldest, link);
     }
 
     if (!interrupted) {
-        printstats(total, sum, max, etotal, entries);
+        printstats(path, &s);
+    }
+}
+
+static apr_status_t remove_directory(apr_pool_t *pool, const char *dir)
+{
+    apr_status_t rv;
+    apr_dir_t *dirp;
+    apr_finfo_t dirent;
+
+    rv = apr_dir_open(&dirp, dir, pool);
+    if (rv == APR_ENOENT) {
+        return rv;
+    }
+    if (rv != APR_SUCCESS) {
+        char errmsg[120];
+        apr_file_printf(errfile, "Could not open directory %s: %s" APR_EOL_STR,
+                dir, apr_strerror(rv, errmsg, sizeof errmsg));
+        return rv;
+    }
+
+    while (apr_dir_read(&dirent, APR_FINFO_DIRENT | APR_FINFO_TYPE, dirp)
+            == APR_SUCCESS) {
+        if (dirent.filetype == APR_DIR) {
+            if (strcmp(dirent.name, ".") && strcmp(dirent.name, "..")) {
+                rv = remove_directory(pool, apr_pstrcat(pool, dir, "/",
+                        dirent.name, NULL));
+                /* tolerate the directory not being empty, the cache may have
+                 * attempted to recreate the directory in the mean time.
+                 */
+                if (APR_SUCCESS != rv && APR_ENOTEMPTY != rv) {
+                    break;
+                }
+            }
+        } else {
+            const char *file = apr_pstrcat(pool, dir, "/", dirent.name, NULL);
+            rv = apr_file_remove(file, pool);
+            if (APR_SUCCESS != rv) {
+                char errmsg[120];
+                apr_file_printf(errfile,
+                        "Could not remove file '%s': %s" APR_EOL_STR, file,
+                        apr_strerror(rv, errmsg, sizeof errmsg));
+                break;
+            }
+        }
+    }
+
+    apr_dir_close(dirp);
+
+    if (rv == APR_SUCCESS) {
+        rv = apr_dir_remove(dir, pool);
+        if (APR_ENOTEMPTY == rv) {
+            rv = APR_SUCCESS;
+        }
+        if (rv != APR_SUCCESS) {
+            char errmsg[120];
+            apr_file_printf(errfile, "Could not remove directory %s: %s" APR_EOL_STR,
+                    dir, apr_strerror(rv, errmsg, sizeof errmsg));
+        }
+    }
+
+    return rv;
+}
+
+static apr_status_t find_directory(apr_pool_t *pool, const char *base,
+        const char *rest)
+{
+    apr_status_t rv;
+    apr_dir_t *dirp;
+    apr_finfo_t dirent;
+    int found = 0, files = 0;
+    const char *header = apr_pstrcat(pool, rest, CACHE_HEADER_SUFFIX, NULL);
+    const char *data = apr_pstrcat(pool, rest, CACHE_DATA_SUFFIX, NULL);
+    const char *vdir = apr_pstrcat(pool, rest, CACHE_HEADER_SUFFIX,
+            CACHE_VDIR_SUFFIX, NULL);
+    const char *dirname = NULL;
+
+    rv = apr_dir_open(&dirp, base, pool);
+    if (rv != APR_SUCCESS) {
+        char errmsg[120];
+        apr_file_printf(errfile, "Could not open directory %s: %s" APR_EOL_STR,
+                base, apr_strerror(rv, errmsg, sizeof errmsg));
+        return rv;
+    }
+
+    rv = APR_ENOENT;
+
+    while (apr_dir_read(&dirent, APR_FINFO_DIRENT | APR_FINFO_TYPE, dirp)
+            == APR_SUCCESS) {
+        int len = strlen(dirent.name);
+        int restlen = strlen(rest);
+        if (dirent.filetype == APR_DIR && !strncmp(rest, dirent.name, len)) {
+            dirname = apr_pstrcat(pool, base, "/", dirent.name, NULL);
+            rv = find_directory(pool, dirname, rest + (len < restlen ? len
+                    : restlen));
+            if (APR_SUCCESS == rv) {
+                found = 1;
+            }
+        }
+        if (dirent.filetype == APR_DIR) {
+            if (!strcmp(dirent.name, vdir)) {
+                files = 1;
+            }
+        }
+        if (dirent.filetype == APR_REG) {
+            if (!strcmp(dirent.name, header) || !strcmp(dirent.name, data)) {
+                files = 1;
+            }
+        }
+    }
+
+    apr_dir_close(dirp);
+
+    if (files) {
+        rv = APR_SUCCESS;
+        if (!dryrun) {
+            const char *remove;
+            apr_status_t status;
+
+            remove = apr_pstrcat(pool, base, "/", header, NULL);
+            status = apr_file_remove(remove, pool);
+            if (status != APR_SUCCESS && status != APR_ENOENT) {
+                char errmsg[120];
+                apr_file_printf(errfile, "Could not remove file %s: %s" APR_EOL_STR,
+                        remove, apr_strerror(status, errmsg, sizeof errmsg));
+                rv = status;
+            }
+
+            remove = apr_pstrcat(pool, base, "/", data, NULL);
+            status = apr_file_remove(remove, pool);
+            if (status != APR_SUCCESS && status != APR_ENOENT) {
+                char errmsg[120];
+                apr_file_printf(errfile, "Could not remove file %s: %s" APR_EOL_STR,
+                        remove, apr_strerror(status, errmsg, sizeof errmsg));
+                rv = status;
+            }
+
+            status = remove_directory(pool, apr_pstrcat(pool, base, "/", vdir, NULL));
+            if (status != APR_SUCCESS && status != APR_ENOENT) {
+                rv = status;
+            }
+        }
+    }
+
+    /* If asked to delete dirs, do so now. We don't care if it fails.
+     * If it fails, it likely means there was something else there.
+     */
+    if (dirname && deldirs && !dryrun) {
+        apr_dir_remove(dirname, pool);
+    }
+
+    if (found) {
+        return APR_SUCCESS;
     }
+
+    return rv;
+}
+
+/**
+ * Delete a specific URL from the cache.
+ */
+static apr_status_t delete_url(apr_pool_t *pool, const char *proxypath, const char *url)
+{
+    apr_md5_ctx_t context;
+    unsigned char digest[16];
+    char tmp[23];
+    int i, k;
+    unsigned int x;
+    static const char enc_table[64] =
+            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_@";
+
+    apr_md5_init(&context);
+    apr_md5_update(&context, (const unsigned char *) url, strlen(url));
+    apr_md5_final(digest, &context);
+
+    /* encode 128 bits as 22 characters, using a modified uuencoding
+     * the encoding is 3 bytes -> 4 characters* i.e. 128 bits is
+     * 5 x 3 bytes + 1 byte -> 5 * 4 characters + 2 characters
+     */
+    for (i = 0, k = 0; i < 15; i += 3) {
+        x = (digest[i] << 16) | (digest[i + 1] << 8) | digest[i + 2];
+        tmp[k++] = enc_table[x >> 18];
+        tmp[k++] = enc_table[(x >> 12) & 0x3f];
+        tmp[k++] = enc_table[(x >> 6) & 0x3f];
+        tmp[k++] = enc_table[x & 0x3f];
+    }
+
+    /* one byte left */
+    x = digest[15];
+    tmp[k++] = enc_table[x >> 2]; /* use up 6 bits */
+    tmp[k++] = enc_table[(x << 4) & 0x3f];
+    tmp[k] = 0;
+
+    /* automatically find the directory levels */
+    return find_directory(pool, proxypath, tmp);
 }
 
 /*
  * usage info
  */
 #define NL APR_EOL_STR
 static void usage(const char *error)
 {
     if (error) {
     	apr_file_printf(errfile, "%s error: %s\n", shortname, error);
     }
-	apr_file_printf(errfile,
+    apr_file_printf(errfile,
     "%s -- program for cleaning the disk cache."                             NL
     "Usage: %s [-Dvtrn] -pPATH -lLIMIT [-PPIDFILE]"                          NL
     "       %s [-nti] -dINTERVAL -pPATH -lLIMIT [-PPIDFILE]"                 NL
+    "       %s [-Dvt] -pPATH URL ..."                                        NL
                                                                              NL
     "Options:"                                                               NL
     "  -d   Daemonize and repeat cache cleaning every INTERVAL minutes."     NL
     "       This option is mutually exclusive with the -D, -v and -r"        NL
     "       options."                                                        NL
                                                                              NL
