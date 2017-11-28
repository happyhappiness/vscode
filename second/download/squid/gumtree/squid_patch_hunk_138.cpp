 
         return -errno;
     }
 
     fd = fs->fd;
     hash_remove_link(hash, (hash_link *) fs);
-    DEBUG(2)
-    fprintf(stderr, "%d CLOSE id %d, FD %d, fs %p\n",
-            (int) mypid,
-            r->id,
-            fs->fd,
-            fs);
+    DEBUG(2) {
+        fprintf(stderr, "%d CLOSE id %d, FD %d, fs %p\n",
+                (int) mypid,
+                r->id,
+                fs->fd,
+                fs);
+    }
     xfree(fs);
     return close(fd);
 }
 
 static int
 do_read(diomsg * r, int len, char *buf)
