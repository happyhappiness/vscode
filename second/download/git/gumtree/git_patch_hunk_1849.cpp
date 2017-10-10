 /*
  * Copyright (c) 2005, Junio C Hamano
  */
 #include "cache.h"
+#include "lockfile.h"
 #include "sigchain.h"
 
-static struct lock_file *lock_file_list;
+static struct lock_file *volatile lock_file_list;
 
-static void remove_lock_file(void)
+static void remove_lock_files(int skip_fclose)
 {
 	pid_t me = getpid();
 
 	while (lock_file_list) {
-		if (lock_file_list->owner == me &&
-		    lock_file_list->filename[0]) {
-			if (lock_file_list->fd >= 0)
-				close(lock_file_list->fd);
-			unlink_or_warn(lock_file_list->filename);
+		if (lock_file_list->owner == me) {
+			/* fclose() is not safe to call in a signal handler */
+			if (skip_fclose)
+				lock_file_list->fp = NULL;
+			rollback_lock_file(lock_file_list);
 		}
 		lock_file_list = lock_file_list->next;
 	}
 }
 
-static void remove_lock_file_on_signal(int signo)
+static void remove_lock_files_on_exit(void)
 {
-	remove_lock_file();
+	remove_lock_files(0);
+}
+
+static void remove_lock_files_on_signal(int signo)
+{
+	remove_lock_files(1);
 	sigchain_pop(signo);
 	raise(signo);
 }
 
 /*
- * p = absolute or relative path name
+ * path = absolute or relative path name
  *
- * Return a pointer into p showing the beginning of the last path name
- * element.  If p is empty or the root directory ("/"), just return p.
+ * Remove the last path name element from path (leaving the preceding
+ * "/", if any).  If path is empty or the root directory ("/"), set
+ * path to the empty string.
  */
-static char *last_path_elm(char *p)
+static void trim_last_path_component(struct strbuf *path)
 {
-	/* r starts pointing to null at the end of the string */
-	char *r = strchr(p, '\0');
-
-	if (r == p)
-		return p; /* just return empty string */
-
-	r--; /* back up to last non-null character */
+	int i = path->len;
 
 	/* back up past trailing slashes, if any */
-	while (r > p && *r == '/')
-		r--;
+	while (i && path->buf[i - 1] == '/')
+		i--;
 
 	/*
-	 * then go backwards until I hit a slash, or the beginning of
-	 * the string
+	 * then go backwards until a slash, or the beginning of the
+	 * string
 	 */
-	while (r > p && *(r-1) != '/')
-		r--;
-	return r;
+	while (i && path->buf[i - 1] != '/')
+		i--;
+
+	strbuf_setlen(path, i);
 }
 
 
 /* We allow "recursive" symbolic links. Only within reason, though */
 #define MAXDEPTH 5
 
 /*
- * p = path that may be a symlink
- * s = full size of p
- *
- * If p is a symlink, attempt to overwrite p with a path to the real
- * file or directory (which may or may not exist), following a chain of
- * symlinks if necessary.  Otherwise, leave p unmodified.
+ * path contains a path that might be a symlink.
  *
- * This is a best-effort routine.  If an error occurs, p will either be
- * left unmodified or will name a different symlink in a symlink chain
- * that started with p's initial contents.
+ * If path is a symlink, attempt to overwrite it with a path to the
+ * real file or directory (which may or may not exist), following a
+ * chain of symlinks if necessary.  Otherwise, leave path unmodified.
  *
- * Always returns p.
+ * This is a best-effort routine.  If an error occurs, path will
+ * either be left unmodified or will name a different symlink in a
+ * symlink chain that started with the original path.
  */
-
-static char *resolve_symlink(char *p, size_t s)
+static void resolve_symlink(struct strbuf *path)
 {
 	int depth = MAXDEPTH;
+	static struct strbuf link = STRBUF_INIT;
 
 	while (depth--) {
-		char link[PATH_MAX];
-		int link_len = readlink(p, link, sizeof(link));
-		if (link_len < 0) {
-			/* not a symlink anymore */
-			return p;
-		}
-		else if (link_len < sizeof(link))
-			/* readlink() never null-terminates */
-			link[link_len] = '\0';
-		else {
-			warning("%s: symlink too long", p);
-			return p;
-		}
+		if (strbuf_readlink(&link, path->buf, path->len) < 0)
+			break;
 
-		if (is_absolute_path(link)) {
+		if (is_absolute_path(link.buf))
 			/* absolute path simply replaces p */
-			if (link_len < s)
-				strcpy(p, link);
-			else {
-				warning("%s: symlink too long", p);
-				return p;
-			}
-		} else {
+			strbuf_reset(path);
+		else
 			/*
-			 * link is a relative path, so I must replace the
+			 * link is a relative path, so replace the
 			 * last element of p with it.
 			 */
-			char *r = (char *)last_path_elm(p);
-			if (r - p + link_len < s)
-				strcpy(r, link);
-			else {
-				warning("%s: symlink too long", p);
-				return p;
-			}
-		}
+			trim_last_path_component(path);
+
+		strbuf_addbuf(path, &link);
 	}
-	return p;
+	strbuf_reset(&link);
 }
 
 /* Make sure errno contains a meaningful value on error */
 static int lock_file(struct lock_file *lk, const char *path, int flags)
 {
-	/*
-	 * subtract 5 from size to make sure there's room for adding
-	 * ".lock" for the lock file name
-	 */
-	static const size_t max_path_len = sizeof(lk->filename) - 5;
+	size_t pathlen = strlen(path);
+
+	if (!lock_file_list) {
+		/* One-time initialization */
+		sigchain_push_common(remove_lock_files_on_signal);
+		atexit(remove_lock_files_on_exit);
+	}
 
-	if (strlen(path) >= max_path_len) {
-		errno = ENAMETOOLONG;
+	if (lk->active)
+		die("BUG: cannot lock_file(\"%s\") using active struct lock_file",
+		    path);
+	if (!lk->on_list) {
+		/* Initialize *lk and add it to lock_file_list: */
+		lk->fd = -1;
+		lk->fp = NULL;
+		lk->active = 0;
+		lk->owner = 0;
+		strbuf_init(&lk->filename, pathlen + LOCK_SUFFIX_LEN);
+		lk->next = lock_file_list;
+		lock_file_list = lk;
+		lk->on_list = 1;
+	} else if (lk->filename.len) {
+		/* This shouldn't happen, but better safe than sorry. */
+		die("BUG: lock_file(\"%s\") called with improperly-reset lock_file object",
+		    path);
+	}
+
+	strbuf_add(&lk->filename, path, pathlen);
+	if (!(flags & LOCK_NO_DEREF))
+		resolve_symlink(&lk->filename);
+	strbuf_addstr(&lk->filename, LOCK_SUFFIX);
+	lk->fd = open(lk->filename.buf, O_RDWR | O_CREAT | O_EXCL, 0666);
+	if (lk->fd < 0) {
+		strbuf_reset(&lk->filename);
 		return -1;
 	}
-	strcpy(lk->filename, path);
-	if (!(flags & LOCK_NODEREF))
-		resolve_symlink(lk->filename, max_path_len);
-	strcat(lk->filename, ".lock");
-	lk->fd = open(lk->filename, O_RDWR | O_CREAT | O_EXCL, 0666);
-	if (0 <= lk->fd) {
-		if (!lock_file_list) {
-			sigchain_push_common(remove_lock_file_on_signal);
-			atexit(remove_lock_file);
-		}
-		lk->owner = getpid();
-		if (!lk->on_list) {
-			lk->next = lock_file_list;
-			lock_file_list = lk;
-			lk->on_list = 1;
-		}
-		if (adjust_shared_perm(lk->filename)) {
-			int save_errno = errno;
-			error("cannot fix permission bits on %s",
-			      lk->filename);
-			errno = save_errno;
-			return -1;
-		}
+	lk->owner = getpid();
+	lk->active = 1;
+	if (adjust_shared_perm(lk->filename.buf)) {
+		int save_errno = errno;
+		error("cannot fix permission bits on %s", lk->filename.buf);
+		rollback_lock_file(lk);
+		errno = save_errno;
+		return -1;
 	}
-	else
-		lk->filename[0] = 0;
 	return lk->fd;
 }
 
 void unable_to_lock_message(const char *path, int err, struct strbuf *buf)
 {
 	if (err == EEXIST) {
