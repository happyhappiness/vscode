   } else {
     DEBUG("rrdtool plugin: No values have been lost "
           "when destroying the cache.");
   }
 
   pthread_mutex_unlock(&cache_lock);
-  return (0);
+  return 0;
 } /* }}} int rrd_cache_destroy */
 
 static int rrd_compare_numeric(const void *a_ptr, const void *b_ptr) {
   int a = *((int *)a_ptr);
   int b = *((int *)b_ptr);
 
   if (a < b)
-    return (-1);
+    return -1;
   else if (a > b)
-    return (1);
+    return 1;
   else
-    return (0);
+    return 0;
 } /* int rrd_compare_numeric */
 
 static int rrd_write(const data_set_t *ds, const value_list_t *vl,
                      user_data_t __attribute__((unused)) * user_data) {
-  struct stat statbuf;
-  char filename[512];
-  char values[512];
-  int status;
 
   if (do_shutdown)
-    return (0);
+    return 0;
 
   if (0 != strcmp(ds->type, vl->type)) {
     ERROR("rrdtool plugin: DS type does not match value list type");
     return -1;
   }
 
+  char filename[PATH_MAX];
   if (value_list_to_filename(filename, sizeof(filename), vl) != 0)
-    return (-1);
+    return -1;
 
+  char values[32 * ds->ds_num];
   if (value_list_to_string(values, sizeof(values), ds, vl) != 0)
-    return (-1);
+    return -1;
 
+  struct stat statbuf = {0};
   if (stat(filename, &statbuf) == -1) {
     if (errno == ENOENT) {
-      status = cu_rrd_create_file(filename, ds, vl, &rrdcreate_config);
-      if (status != 0)
-        return (-1);
-      else if (rrdcreate_config.async)
-        return (0);
+      if (cu_rrd_create_file(filename, ds, vl, &rrdcreate_config) != 0) {
+        return -1;
+      } else if (rrdcreate_config.async) {
+        return 0;
+      }
     } else {
       char errbuf[1024];
-      ERROR("stat(%s) failed: %s", filename,
+      ERROR("rrdtool plugin: stat(%s) failed: %s", filename,
             sstrerror(errno, errbuf, sizeof(errbuf)));
-      return (-1);
+      return -1;
     }
   } else if (!S_ISREG(statbuf.st_mode)) {
-    ERROR("stat(%s): Not a regular file!", filename);
-    return (-1);
+    ERROR("rrdtool plugin: stat(%s): Not a regular file!", filename);
+    return -1;
   }
 
-  status = rrd_cache_insert(filename, values, vl->time);
-
-  return (status);
+  return rrd_cache_insert(filename, values, vl->time);
 } /* int rrd_write */
 
 static int rrd_flush(cdtime_t timeout, const char *identifier,
                      __attribute__((unused)) user_data_t *user_data) {
   pthread_mutex_lock(&cache_lock);
 
   if (cache == NULL) {
     pthread_mutex_unlock(&cache_lock);
-    return (0);
+    return 0;
   }
 
   rrd_cache_flush_identifier(timeout, identifier);
 
   pthread_mutex_unlock(&cache_lock);
-  return (0);
+  return 0;
 } /* int rrd_flush */
 
 static int rrd_config(const char *key, const char *value) {
   if (strcasecmp("CacheTimeout", key) == 0) {
     double tmp = atof(value);
     if (tmp < 0) {
       fprintf(stderr, "rrdtool: `CacheTimeout' must "
                       "be greater than 0.\n");
       ERROR("rrdtool: `CacheTimeout' must "
             "be greater than 0.\n");
-      return (1);
+      return 1;
     }
     cache_timeout = DOUBLE_TO_CDTIME_T(tmp);
   } else if (strcasecmp("CacheFlush", key) == 0) {
-    int tmp = atoi(value);
+    double tmp = atof(value);
     if (tmp < 0) {
       fprintf(stderr, "rrdtool: `CacheFlush' must "
                       "be greater than 0.\n");
       ERROR("rrdtool: `CacheFlush' must "
             "be greater than 0.\n");
-      return (1);
+      return 1;
     }
-    cache_flush_timeout = tmp;
+    cache_flush_timeout = DOUBLE_TO_CDTIME_T(tmp);
   } else if (strcasecmp("DataDir", key) == 0) {
     char *tmp;
     size_t len;
 
     tmp = strdup(value);
     if (tmp == NULL) {
       ERROR("rrdtool plugin: strdup failed.");
-      return (1);
+      return 1;
     }
 
     len = strlen(tmp);
     while ((len > 0) && (tmp[len - 1] == '/')) {
       len--;
       tmp[len] = 0;
     }
 
     if (len == 0) {
       ERROR("rrdtool plugin: Invalid \"DataDir\" option.");
       sfree(tmp);
-      return (1);
+      return 1;
     }
 
     if (datadir != NULL) {
       sfree(datadir);
     }
 
