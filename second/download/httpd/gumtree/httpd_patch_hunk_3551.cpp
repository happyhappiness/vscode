         }
         if (!unsolicited && !ufrag) {
             ufrag = 1;
         }
         apr_file_printf(errfile, "unsolicited size %d.%d%c" APR_EOL_STR,
                         (int)(unsolicited), (int)(ufrag), utype);
-     }
-     apr_file_printf(errfile, "size limit %d.0%c" APR_EOL_STR,
-                     (int)(s->max), mtype);
-     apr_file_printf(errfile, "total size was %d.%d%c, total size now "
-                              "%d.%d%c" APR_EOL_STR,
-                     (int)(s->total), (int)(tfrag), ttype,
-                     (int)(s->sum), (int)(sfrag), stype);
-     apr_file_printf(errfile, "total entries was %d, total entries now %d"
-                              APR_EOL_STR, (int)(s->etotal),
-                              (int)(s->entries));
-     apr_file_printf(errfile, "%d entries deleted (%d from future, %d "
-                              "expired, %d fresh)" APR_EOL_STR,
-                     (int)(s->etotal - s->entries), (int)(s->dfuture),
-                     (int)(s->dexpired), (int)(s->dfresh));
+    }
+    apr_file_printf(errfile, "size limit %" APR_OFF_T_FMT ".0%c" APR_EOL_STR,
+            s->max, mtype);
+    apr_file_printf(errfile, "inodes limit %" APR_OFF_T_FMT APR_EOL_STR,
+            s->inodes);
+    apr_file_printf(
+            errfile,
+            "total size was %" APR_OFF_T_FMT ".%" APR_OFF_T_FMT "%c, total size now "
+            "%" APR_OFF_T_FMT ".%" APR_OFF_T_FMT "%c" APR_EOL_STR, s->total,
+            tfrag, ttype, s->sum, sfrag, stype);
+    apr_file_printf(errfile, "total inodes was %" APR_OFF_T_FMT
+            ", total %sinodes now "
+            "%" APR_OFF_T_FMT APR_EOL_STR, s->ntotal, dryrun && deldirs ? "estimated "
+            : "", s->nodes);
+    apr_file_printf(
+            errfile,
+            "total entries was %" APR_OFF_T_FMT ", total entries now %" APR_OFF_T_FMT
+            APR_EOL_STR, s->etotal, s->entries);
+    apr_file_printf(
+            errfile,
+            "%" APR_OFF_T_FMT " entries deleted (%" APR_OFF_T_FMT " from future, %"
+            APR_OFF_T_FMT " expired, %" APR_OFF_T_FMT " fresh)" APR_EOL_STR,
+            (s->etotal - s->entries), s->dfuture, s->dexpired, s->dfresh);
+}
+
+/**
+ * Round the value up to the given threshold.
+ */
+static apr_size_t round_up(apr_size_t val, apr_off_t round) {
+    if (round > 1) {
+        return (apr_size_t)(((val + round - 1) / round) * round);
+    }
+    return val;
 }
 
 /*
- * delete a single file
+ * delete parent directories
  */
-static void delete_file(char *path, char *basename, apr_pool_t *pool)
+static void delete_parent(const char *path, const char *basename,
+        apr_off_t *nodes, apr_pool_t *pool)
 {
-    char *nextpath;
+    char *nextpath, *name;
     apr_pool_t *p;
 
-    if (dryrun) {
-        return;
+    /* temp pool, otherwise lots of memory could be allocated */
+    apr_pool_create(&p, pool);
+    name = apr_pstrdup(p, basename);
+
+    /* If asked to delete dirs, do so now. We don't care if it fails.
+     * If it fails, it likely means there was something else there.
+     */
+    if (deldirs && !dryrun) {
+        const char *vary;
+        char *end = strrchr(name, '/');
+        while (end) {
+            *end = 0;
+
+            /* remove the directory */
+            nextpath = apr_pstrcat(p, path, "/", name, NULL);
+            if (!apr_dir_remove(nextpath, p)) {
+                (*nodes)--;
+
+                /* vary directory found? */
+                vary = strstr(name, CACHE_VDIR_SUFFIX);
+                if (vary && !vary[sizeof(CACHE_VDIR_SUFFIX) - 1]) {
+                    nextpath = apr_pstrcat(p, path, "/", apr_pstrndup(p, name, vary
+                            - name), NULL);
+                    if (!apr_file_remove(nextpath, p)) {
+                        (*nodes)--;
+                    }
+                }
+
+            }
+            else {
+                break;
+            }
+            end = strrchr(name, '/');
+        }
     }
 
+    apr_pool_destroy(p);
+
+    if (benice) {
+        if (++delcount >= DELETE_NICE) {
+            apr_sleep(NICE_DELAY);
+            delcount = 0;
+        }
+    }
+
+}
+
+/*
+ * delete a single file
+ */
+static void delete_file(char *path, char *basename, apr_off_t *nodes,
+        apr_pool_t *pool)
+{
+    char *nextpath;
+    apr_pool_t *p;
+
     /* temp pool, otherwise lots of memory could be allocated */
     apr_pool_create(&p, pool);
     nextpath = apr_pstrcat(p, path, "/", basename, NULL);
-    apr_file_remove(nextpath, p);
+
+    if (dryrun) {
+        apr_finfo_t finfo;
+        if (!apr_stat(&finfo, nextpath, APR_FINFO_NLINK, p)) {
+            (*nodes)--;
+        }
+    }
+    else if (!apr_file_remove(nextpath, p)) {
+        (*nodes)--;
+    }
+
     apr_pool_destroy(p);
 
     if (benice) {
         if (++delcount >= DELETE_NICE) {
             apr_sleep(NICE_DELAY);
             delcount = 0;
         }
     }
+
+    delete_parent(path, basename, nodes, pool);
+
 }
 
 /*
  * delete cache file set
  */
-static void delete_entry(char *path, char *basename, apr_pool_t *pool)
+static void delete_entry(char *path, char *basename, apr_off_t *nodes,
+        apr_pool_t *pool)
 {
     char *nextpath;
     apr_pool_t *p;
 
-    if (dryrun) {
-        return;
-    }
-
     /* temp pool, otherwise lots of memory could be allocated */
     apr_pool_create(&p, pool);
 
     nextpath = apr_pstrcat(p, path, "/", basename, CACHE_HEADER_SUFFIX, NULL);
-    apr_file_remove(nextpath, p);
+    if (dryrun) {
+        apr_finfo_t finfo;
+        if (!apr_stat(&finfo, nextpath, APR_FINFO_NLINK, p)) {
+            (*nodes)--;
+        }
+    }
+    else if (!apr_file_remove(nextpath, p)) {
+        (*nodes)--;
+    }
 
     nextpath = apr_pstrcat(p, path, "/", basename, CACHE_DATA_SUFFIX, NULL);
-    apr_file_remove(nextpath, p);
+    if (dryrun) {
+        apr_finfo_t finfo;
+        if (!apr_stat(&finfo, nextpath, APR_FINFO_NLINK, p)) {
+            (*nodes)--;
+        }
+    }
+    else if (!apr_file_remove(nextpath, p)) {
+        (*nodes)--;
+    }
 
     apr_pool_destroy(p);
 
     if (benice) {
         delcount += 2;
         if (delcount >= DELETE_NICE) {
             apr_sleep(NICE_DELAY);
             delcount = 0;
         }
     }
+
+    delete_parent(path, basename, nodes, pool);
+
+}
+
+/*
+ * list the cache directory tree
+ */
+static int list_urls(char *path, apr_pool_t *pool, apr_off_t round)
+{
+    apr_dir_t *dir;
+    apr_finfo_t info;
+    apr_size_t len;
+    apr_pool_t *p;
+    apr_file_t *fd;
+    const char *ext, *nextpath;
+    char *url;
+    apr_uint32_t format;
+    disk_cache_info_t disk_info;
+
+    apr_pool_create(&p, pool);
+
+    if (apr_dir_open(&dir, path, p) != APR_SUCCESS) {
+        return 1;
+    }
+
+    while (apr_dir_read(&info, 0, dir) == APR_SUCCESS && !interrupted) {
+
+        if (info.filetype == APR_DIR) {
+            if (!strcmp(info.name, ".") || !strcmp(info.name, "..")) {
+                continue;
+            }
+
+            if (list_urls(apr_pstrcat(p, path, "/", info.name, NULL), pool, round)) {
+                return 1;
+            }
+        }
+
+        else if (info.filetype == APR_REG) {
+
+            ext = strchr(info.name, '.');
+
+            if (ext && !strcasecmp(ext, CACHE_HEADER_SUFFIX)) {
+
+                nextpath = apr_pstrcat(p, path, "/", info.name, NULL);
+
+                if (apr_file_open(&fd, nextpath, APR_FOPEN_READ
+                        | APR_FOPEN_BINARY, APR_OS_DEFAULT, p) == APR_SUCCESS) {
+                    len = sizeof(format);
+                    if (apr_file_read_full(fd, &format, len, &len)
+                            == APR_SUCCESS) {
+                        if (format == DISK_FORMAT_VERSION) {
+                            apr_off_t offset = 0;
+
+                            apr_file_seek(fd, APR_SET, &offset);
+
+                            len = sizeof(disk_cache_info_t);
+
+                            if (apr_file_read_full(fd, &disk_info, len, &len)
+                                    == APR_SUCCESS) {
+                                len = disk_info.name_len;
+                                url = apr_palloc(p, len + 1);
+                                url[len] = 0;
+
+                                if (apr_file_read_full(fd, url, len, &len)
+                                        == APR_SUCCESS) {
+
+                                    if (listextended) {
+                                        apr_finfo_t hinfo, dinfo;
+
+                                        /* stat the header file */
+                                        if (APR_SUCCESS != apr_file_info_get(
+                                                &hinfo, APR_FINFO_SIZE, fd)) {
+                                            /* ignore the file */
+                                        }
+                                        else if (disk_info.has_body && APR_SUCCESS
+                                                != apr_stat(
+                                                        &dinfo,
+                                                        apr_pstrcat(
+                                                                p,
+                                                                path,
+                                                                "/",
+                                                                apr_pstrndup(
+                                                                        p,
+                                                                        info.name,
+                                                                        ext
+                                                                                - info.name),
+                                                                CACHE_DATA_SUFFIX,
+                                                                NULL),
+                                                        APR_FINFO_SIZE
+                                                                | APR_FINFO_IDENT,
+                                                        p)) {
+                                            /* ignore the file */
+                                        }
+                                        else if (disk_info.has_body && (dinfo.device
+                                                != disk_info.device
+                                                || dinfo.inode
+                                                        != disk_info.inode)) {
+                                            /* ignore the file */
+                                        }
+                                        else {
+
+                                            apr_file_printf(
+                                                    outfile,
+                                                    "%s %" APR_SIZE_T_FMT
+                                                    " %" APR_SIZE_T_FMT
+                                                    " %d %" APR_SIZE_T_FMT
+                                                    " %" APR_TIME_T_FMT
+                                                    " %" APR_TIME_T_FMT
+                                                    " %" APR_TIME_T_FMT
+                                                    " %" APR_TIME_T_FMT
+                                                    " %d %d\n",
+                                                    url,
+                                                    round_up((apr_size_t)hinfo.size, round),
+                                                    round_up(
+                                                            disk_info.has_body ? (apr_size_t)dinfo.size
+                                                                    : 0, round),
+                                                    disk_info.status,
+                                                    disk_info.entity_version,
+                                                    disk_info.date,
+                                                    disk_info.expire,
+                                                    disk_info.request_time,
+                                                    disk_info.response_time,
+                                                    disk_info.has_body,
+                                                    disk_info.header_only);
+                                        }
+                                    }
+                                    else {
+                                        apr_finfo_t dinfo;
+
+                                        /* stat the data file */
+                                        if (disk_info.has_body && APR_SUCCESS
+                                                != apr_stat(
+                                                        &dinfo,
+                                                        apr_pstrcat(
+                                                                p,
+                                                                path,
+                                                                "/",
+                                                                apr_pstrndup(
+                                                                        p,
+                                                                        info.name,
+                                                                        ext
+                                                                                - info.name),
+                                                                CACHE_DATA_SUFFIX,
+                                                                NULL),
+                                                        APR_FINFO_SIZE
+                                                                | APR_FINFO_IDENT,
+                                                        p)) {
+                                            /* ignore the file */
+                                        }
+                                        else if (disk_info.has_body && (dinfo.device
+                                                != disk_info.device
+                                                || dinfo.inode
+                                                        != disk_info.inode)) {
+                                            /* ignore the file */
+                                        }
+                                        else {
+                                            apr_file_printf(outfile, "%s\n",
+                                                    url);
+                                        }
+                                    }
+                                }
+
+                                break;
+                            }
+                        }
+                    }
+                    apr_file_close(fd);
+
+                }
+            }
+        }
+
+    }
+
+    apr_dir_close(dir);
+
+    if (interrupted) {
+        return 1;
+    }
+
+    apr_pool_destroy(p);
+
+    if (benice) {
+        apr_sleep(NICE_DELAY);
+    }
+
+    if (interrupted) {
+        return 1;
+    }
+
+    return 0;
 }
 
 /*
  * walk the cache directory tree
  */
-static int process_dir(char *path, apr_pool_t *pool)
+static int process_dir(char *path, apr_pool_t *pool, apr_off_t *nodes)
 {
     apr_dir_t *dir;
     apr_pool_t *p;
     apr_hash_t *h;
     apr_hash_index_t *i;
     apr_file_t *fd;
     apr_status_t status;
     apr_finfo_t info;
     apr_size_t len;
     apr_time_t current, deviation;
-    char *nextpath, *base, *ext, *orig_basename;
+    char *nextpath, *base, *ext;
     APR_RING_ENTRY(_direntry) anchor;
     DIRENTRY *d, *t, *n;
     ENTRY *e;
     int skip, retries;
     disk_cache_info_t disk_info;
 
     APR_RING_INIT(&anchor, _direntry, link);
     apr_pool_create(&p, pool);
     h = apr_hash_make(p);
     fd = NULL;
-    skip = 0;
     deviation = MAXDEVIATION * APR_USEC_PER_SEC;
 
     if (apr_dir_open(&dir, path, p) != APR_SUCCESS) {
         return 1;
     }
 
