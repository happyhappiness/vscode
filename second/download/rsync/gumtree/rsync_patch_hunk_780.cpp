 
 #include "rsync.h"
 
 extern int dry_run;
 extern int verbose;
 extern int make_backups;
+extern struct file_list *the_file_list;
 
-#if SUPPORT_HARD_LINKS
-static int hlink_compare(struct file_struct **file1, struct file_struct **file2)
+#ifdef SUPPORT_HARD_LINKS
+
+#define FPTR(i) (the_file_list->files[i])
+#define LINKED(p1,p2) (FPTR(p1)->F_DEV == FPTR(p2)->F_DEV \
+		    && FPTR(p1)->F_INODE == FPTR(p2)->F_INODE)
+
+static int hlink_compare(int *int1, int *int2)
 {
-	struct file_struct *f1 = *file1;
-	struct file_struct *f2 = *file2;
+	struct file_struct *f1 = FPTR(*int1);
+	struct file_struct *f2 = FPTR(*int2);
 
 	if (f1->F_DEV != f2->F_DEV)
 		return (int) (f1->F_DEV > f2->F_DEV ? 1 : -1);
 
 	if (f1->F_INODE != f2->F_INODE)
 		return (int) (f1->F_INODE > f2->F_INODE ? 1 : -1);
 
-	return file_compare(file1, file2);
+	return f_name_cmp(f1, f2);
 }
 
-static struct file_struct **hlink_list;
+static int *hlink_list;
 static int hlink_count;
 
-#define LINKED(p1,p2) ((p1)->F_DEV == (p2)->F_DEV \
-		    && (p1)->F_INODE == (p2)->F_INODE)
-
 /* Analyze the data in the hlink_list[], remove items that aren't multiply
  * linked, and replace the dev+inode data with the hlindex+next linked list. */
-static void link_idev_data(struct file_list *flist)
+static void link_idev_data(void)
 {
-	struct file_struct *head;
-	int from, to, start;
+	int head, from, to, start;
 
 	alloc_pool_t hlink_pool;
-	alloc_pool_t idev_pool = flist->hlink_pool;
+	alloc_pool_t idev_pool = the_file_list->hlink_pool;
 
 	hlink_pool = pool_create(128 * 1024, sizeof (struct hlink),
 	    out_of_memory, POOL_INTERN);
 
 	for (from = to = 0; from < hlink_count; from++) {
 		start = from;
 		head = hlink_list[start];
 		while (from < hlink_count-1
 		    && LINKED(hlink_list[from], hlink_list[from+1])) {
-			pool_free(idev_pool, 0, hlink_list[from]->link_u.idev);
-			hlink_list[from]->link_u.links = pool_talloc(hlink_pool,
+			pool_free(idev_pool, 0, FPTR(hlink_list[from])->link_u.idev);
+			FPTR(hlink_list[from])->link_u.links = pool_talloc(hlink_pool,
 			    struct hlink, 1, "hlink_list");
 
-			hlink_list[from]->F_HLINDEX = to;
-			hlink_list[from]->F_NEXT = hlink_list[from+1];
+			FPTR(hlink_list[from])->F_HLINDEX = to;
+			FPTR(hlink_list[from])->F_NEXT = hlink_list[from+1];
 			from++;
 		}
 		if (from > start) {
-			pool_free(idev_pool, 0, hlink_list[from]->link_u.idev);
-			hlink_list[from]->link_u.links = pool_talloc(hlink_pool,
+			pool_free(idev_pool, 0, FPTR(hlink_list[from])->link_u.idev);
+			FPTR(hlink_list[from])->link_u.links = pool_talloc(hlink_pool,
 			    struct hlink, 1, "hlink_list");
 
-			hlink_list[from]->F_HLINDEX = to;
-			hlink_list[from]->F_NEXT = head;
-			hlink_list[from]->flags |= FLAG_HLINK_EOL;
+			FPTR(head)->flags |= FLAG_HLINK_TOL;
+			FPTR(hlink_list[from])->F_HLINDEX = to;
+			FPTR(hlink_list[from])->F_NEXT = head;
+			FPTR(hlink_list[from])->flags |= FLAG_HLINK_EOL;
 			hlink_list[to++] = head;
 		} else {
-			pool_free(idev_pool, 0, head->link_u.idev);
-			head->link_u.idev = NULL;
+			pool_free(idev_pool, 0, FPTR(head)->link_u.idev);
+			FPTR(head)->link_u.idev = NULL;
 		}
 	}
 
 	if (!to) {
 		free(hlink_list);
 		hlink_list = NULL;
 		pool_destroy(hlink_pool);
 		hlink_pool = NULL;
 	} else {
 		hlink_count = to;
-		if (!(hlink_list = realloc_array(hlink_list,
-		    struct file_struct *, hlink_count)))
+		hlink_list = realloc_array(hlink_list, int, hlink_count);
+		if (!hlink_list)
 			out_of_memory("init_hard_links");
 	}
-	flist->hlink_pool = hlink_pool;
+	the_file_list->hlink_pool = hlink_pool;
 	pool_destroy(idev_pool);
 }
 #endif
 
-void init_hard_links(struct file_list *flist)
+void init_hard_links(void)
 {
-#if SUPPORT_HARD_LINKS
+#ifdef SUPPORT_HARD_LINKS
 	int i;
 
-	if (flist->count < 2)
+	if (the_file_list->count < 2)
 		return;
 
 	if (hlink_list)
 		free(hlink_list);
 
-	if (!(hlink_list = new_array(struct file_struct *, flist->count)))
+	if (!(hlink_list = new_array(int, the_file_list->count)))
 		out_of_memory("init_hard_links");
 
 	hlink_count = 0;
-	for (i = 0; i < flist->count; i++) {
-		if (flist->files[i]->link_u.idev)
-			hlink_list[hlink_count++] = flist->files[i];
+	for (i = 0; i < the_file_list->count; i++) {
+		if (FPTR(i)->link_u.idev)
+			hlink_list[hlink_count++] = i;
 	}
 
 	qsort(hlink_list, hlink_count,
 	    sizeof hlink_list[0], (int (*)()) hlink_compare);
 
 	if (!hlink_count) {
 		free(hlink_list);
 		hlink_list = NULL;
 	} else
-		link_idev_data(flist);
+		link_idev_data();
 #endif
 }
 
-int hard_link_check(struct file_struct *file, int skip)
+int hard_link_check(struct file_struct *file, int ndx, int skip)
 {
-#if SUPPORT_HARD_LINKS
+#ifdef SUPPORT_HARD_LINKS
 	if (!hlink_list || !file->link_u.links)
 		return 0;
 	if (skip && !(file->flags & FLAG_HLINK_EOL))
 		hlink_list[file->F_HLINDEX] = file->F_NEXT;
-	if (hlink_list[file->F_HLINDEX] != file) {
-		if (verbose > 1) {
+	if (hlink_list[file->F_HLINDEX] != ndx) {
+		if (verbose > 2) {
 			rprintf(FINFO, "\"%s\" is a hard link\n",
-			    f_name(file));
+				safe_fname(f_name(file)));
 		}
 		return 1;
 	}
 #endif
 	return 0;
 }
 
-#if SUPPORT_HARD_LINKS
-static void hard_link_one(char *hlink1, char *hlink2)
+#ifdef SUPPORT_HARD_LINKS
+int hard_link_one(struct file_struct *file, int ndx, char *fname,
+		  int statret, STRUCT_STAT *st, char *toname, int terse,
+		  int itemizing, enum logcode code)
 {
-	if (do_link(hlink1, hlink2)) {
+	if (do_link(toname, fname)) {
 		if (verbose) {
-			rsyserr(FINFO, errno, "link %s => %s failed",
-				hlink2, hlink1);
+			rsyserr(FERROR, errno, "link %s => %s failed",
+				full_fname(fname), safe_fname(toname));
 		}
+		return -1;
+	}
+
+	if (itemizing) {
+		itemize(file, ndx, statret, st,
+			ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS, 0,
+			terse ? "" : toname);
+	}
+	if (code && verbose && !terse) {
+		rprintf(code, "%s => %s\n",
+			safe_fname(fname), safe_fname(toname));
 	}
-	else if (verbose)
-		rprintf(FINFO, "%s => %s\n", hlink2, hlink1);
+	return 0;
 }
 #endif
 
 
-
-/**
- * Create any hard links in the global hlink_list.  They were put
- * there by running init_hard_links on the filelist.
- **/
-void do_hard_links(void)
+void hard_link_cluster(struct file_struct *file, int master, int itemizing,
+		       enum logcode code)
 {
-#if SUPPORT_HARD_LINKS
-	struct file_struct *file, *first;
+#ifdef SUPPORT_HARD_LINKS
 	char hlink1[MAXPATHLEN];
 	char *hlink2;
 	STRUCT_STAT st1, st2;
-	int i;
+	int statret, ndx = master;
 
-	if (!hlink_list)
+	if (link_stat(f_name_to(file, hlink1), &st1, 0) < 0)
 		return;
-
-	for (i = 0; i < hlink_count; i++) {
-		first = file = hlink_list[i];
-		if (link_stat(f_name_to(first, hlink1), &st1, 0) < 0)
+	if (!(file->flags & FLAG_HLINK_TOL)) {
+		while (!(file->flags & FLAG_HLINK_EOL)) {
+			ndx = file->F_NEXT;
+			file = FPTR(ndx);
+		}
+	}
+	do {
+		ndx = file->F_NEXT;
+		file = FPTR(ndx);
+		if (ndx == master)
 			continue;
-		while ((file = file->F_NEXT) != first) {
-			hlink2 = f_name(file);
-			if (link_stat(hlink2, &st2, 0) == 0) {
-				if (st2.st_dev == st1.st_dev
-				    && st2.st_ino == st1.st_ino)
-					continue;
-				if (make_backups) {
-					if (!make_backup(hlink2))
-						continue;
-				} else if (robust_unlink(hlink2)) {
-					if (verbose > 0) {
-						rsyserr(FINFO, errno,
-							"unlink %s failed",
-							full_fname(hlink2));
-					}
+		hlink2 = f_name(file);
+		if ((statret = link_stat(hlink2, &st2, 0)) == 0) {
+			if (st2.st_dev == st1.st_dev
+			    && st2.st_ino == st1.st_ino) {
+				if (itemizing) {
+					itemize(file, ndx, statret, &st2,
+						ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS,
+						0, "");
+				}
+				continue;
+			}
+			if (make_backups) {
+				if (!make_backup(hlink2))
 					continue;
+			} else if (robust_unlink(hlink2)) {
+				if (verbose > 0) {
+					rsyserr(FINFO, errno,
+						"unlink %s failed",
+						full_fname(hlink2));
 				}
+				continue;
 			}
-			hard_link_one(hlink1, hlink2);
 		}
-	}
+		hard_link_one(file, ndx, hlink2, statret,
+			      &st2, hlink1, 0, itemizing, code);
+	} while (!(file->flags & FLAG_HLINK_EOL));
 #endif
 }
