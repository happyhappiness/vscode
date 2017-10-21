 		s1++; s2++;
 	}
 	
 	return (int)*s1 - (int)*s2;
 }
 
-static OFF_T  last_ofs;
-static struct timeval print_time;
-static struct timeval start_time;
-static OFF_T  start_ofs;
-
-static unsigned long msdiff(struct timeval *t1, struct timeval *t2)
-{
-    return (t2->tv_sec - t1->tv_sec) * 1000
-        + (t2->tv_usec - t1->tv_usec) / 1000;
-}
 
 
 /**
- * @param ofs Current position in file
- * @param size Total size of file
- * @param is_last True if this is the last time progress will be
- * printed for this file, so we should output a newline.  (Not
- * necessarily the same as all bytes being received.)
+ * Determine if a symlink points outside the current directory tree.
+ * This is considered "unsafe" because e.g. when mirroring somebody
+ * else's machine it might allow them to establish a symlink to
+ * /etc/passwd, and then read it through a web server.
+ *
+ * Null symlinks and absolute symlinks are always unsafe.
+ *
+ * Basically here we are concerned with symlinks whose target contains
+ * "..", because this might cause us to walk back up out of the
+ * transferred directory.  We are not allowed to go back up and
+ * reenter.
+ *
+ * @param dest Target of the symlink in question.
+ *
+ * @param src Top source directory currently applicable.  Basically this
+ * is the first parameter to rsync in a simple invocation, but it's
+ * modified by flist.c in slightly complex ways.
+ *
+ * @retval True if unsafe
+ * @retval False is unsafe
+ *
+ * @sa t_unsafe.c
  **/
-static void rprint_progress(OFF_T ofs, OFF_T size, struct timeval *now,
-			    int is_last)
-{
-    int           pct  = (ofs == size) ? 100 : (int)((100.0*ofs)/size);
-    unsigned long diff = msdiff(&start_time, now);
-    double        rate = diff ? (double) (ofs-start_ofs) * 1000.0 / diff / 1024.0 : 0;
-    const char    *units;
-    /* If we've finished transferring this file, show the time taken;
-     * otherwise show expected time to complete.  That's kind of
-     * inconsistent, but people can probably cope.  Hopefully we'll
-     * get more consistent and complete progress reporting soon. --
-     * mbp */
-    double        remain = is_last
-                        ? (double) diff / 1000.0
-                        : rate ? (double) (size-ofs) / rate / 1000.0 : 0.0;
-    int 	  remain_h, remain_m, remain_s;
-
-    if (rate > 1024*1024) {
-	    rate /= 1024.0 * 1024.0;
-	    units = "GB/s";
-    } else if (rate > 1024) {
-	    rate /= 1024.0;
-	    units = "MB/s";
-    } else {
-	    units = "kB/s";
-    }
-
-    remain_s = (int) remain % 60;
-    remain_m = (int) (remain / 60.0) % 60;
-    remain_h = (int) (remain / 3600.0);
-    
-    rprintf(FINFO, "%12.0f %3d%% %7.2f%s %4d:%02d:%02d%s",
-	    (double) ofs, pct, rate, units,
-	    remain_h, remain_m, remain_s,
-	    is_last ? "\n" : "\r");
-}
-
-void end_progress(OFF_T size)
-{
-	extern int do_progress, am_server;
-
-	if (do_progress && !am_server) {
-        	struct timeval now;
-                gettimeofday(&now, NULL);
-                rprint_progress(size, size, &now, True);
-	}
-	last_ofs   = 0;
-        start_ofs  = 0;
-        print_time.tv_sec  = print_time.tv_usec  = 0;
-        start_time.tv_sec  = start_time.tv_usec  = 0;
-}
-
-void show_progress(OFF_T ofs, OFF_T size)
-{
-	extern int do_progress, am_server;
-        struct timeval now;
-
-        gettimeofday(&now, NULL);
-
-        if (!start_time.tv_sec && !start_time.tv_usec) {
-        	start_time.tv_sec  = now.tv_sec;
-                start_time.tv_usec = now.tv_usec;
-                start_ofs          = ofs;
-        }
-
-	if (do_progress
-            && !am_server
-            && ofs > last_ofs + 1000
-            && msdiff(&print_time, &now) > 250) {
-        	rprint_progress(ofs, size, &now, False);
-                last_ofs = ofs;
-                print_time.tv_sec  = now.tv_sec;
-                print_time.tv_usec = now.tv_usec;
-	}
-}
-
-/* determine if a symlink points outside the current directory tree */
-int unsafe_symlink(char *dest, char *src)
+int unsafe_symlink(const char *dest, const char *src)
 {
-	char *tok;
+	const char *name, *slash;
 	int depth = 0;
 
 	/* all absolute and null symlinks are unsafe */
-	if (!dest || !(*dest) || (*dest == '/')) return 1;
-
-	src = strdup(src);
-	if (!src) out_of_memory("unsafe_symlink");
+	if (!dest || !*dest || *dest == '/') return 1;
 
 	/* find out what our safety margin is */
-	for (tok=strtok(src,"/"); tok; tok=strtok(NULL,"/")) {
-		if (strcmp(tok,"..") == 0) {
+	for (name = src; (slash = strchr(name, '/')) != 0; name = slash+1) {
+		if (strncmp(name, "../", 3) == 0) {
 			depth=0;
-		} else if (strcmp(tok,".") == 0) {
+		} else if (strncmp(name, "./", 2) == 0) {
 			/* nothing */
 		} else {
 			depth++;
 		}
 	}
-	free(src);
-
-	/* drop by one to account for the filename portion */
-	depth--;
+	if (strcmp(name, "..") == 0)
+		depth = 0;
 
-	dest = strdup(dest);
-	if (!dest) out_of_memory("unsafe_symlink");
-
-	for (tok=strtok(dest,"/"); tok; tok=strtok(NULL,"/")) {
-		if (strcmp(tok,"..") == 0) {
-			depth--;
-		} else if (strcmp(tok,".") == 0) {
+	for (name = dest; (slash = strchr(name, '/')) != 0; name = slash+1) {
+		if (strncmp(name, "../", 3) == 0) {
+			/* if at any point we go outside the current directory
+			   then stop - it is unsafe */
+			if (--depth < 0)
+				return 1;
+		} else if (strncmp(name, "./", 2) == 0) {
 			/* nothing */
 		} else {
 			depth++;
 		}
-		/* if at any point we go outside the current directory then
-		   stop - it is unsafe */
-		if (depth < 0) break;
 	}
+	if (strcmp(name, "..") == 0)
+		depth--;
 
-	free(dest);
 	return (depth < 0);
 }
 
 
-/****************************************************************************
-  return the date and time as a string
-****************************************************************************/
+/**
+ * Return the date and time as a string
+ **/
 char *timestring(time_t t)
 {
 	static char TimeBuf[200];
 	struct tm *tm = localtime(&t);
 
 #ifdef HAVE_STRFTIME
