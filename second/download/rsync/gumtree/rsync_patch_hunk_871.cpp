 /*
  * Routines to support hard-linking.
  *
  * Copyright (C) 1996 Andrew Tridgell
  * Copyright (C) 1996 Paul Mackerras
  * Copyright (C) 2002 Martin Pool <mbp@samba.org>
- * Copyright (C) 2004, 2005, 2006 Wayne Davison
+ * Copyright (C) 2004-2008 Wayne Davison
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
- * the Free Software Foundation; either version 2 of the License, or
+ * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License along
- * with this program; if not, write to the Free Software Foundation, Inc.,
- * 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
+ * with this program; if not, visit the http://fsf.org website.
  */
 
 #include "rsync.h"
 
 extern int verbose;
+extern int dry_run;
+extern int list_only;
+extern int am_sender;
+extern int inc_recurse;
 extern int do_xfers;
 extern int link_dest;
+extern int preserve_acls;
 extern int make_backups;
+extern int protocol_version;
 extern int remove_source_files;
 extern int stdout_format_has_i;
+extern int maybe_ATTRS_REPORT;
+extern int unsort_ndx;
 extern char *basis_dir[];
-extern struct file_list *the_file_list;
+extern struct file_list *cur_flist;
 
 #ifdef SUPPORT_HARD_LINKS
 
-#define SKIPPED_LINK (-1)
-#define FINISHED_LINK (-2)
+/* Starting with protocol 30, we use a simple hashtable on the sending side
+ * for hashing the st_dev and st_ino info.  The receiving side gets told
+ * (via flags and a "group index") which items are hard-linked together, so
+ * we can avoid the pool of dev+inode data.  For incremental recursion mode,
+ * the receiver will use a ndx hash to remember old pathnames. */
 
-#define FPTR(i) (the_file_list->files[i])
-#define LINKED(p1,p2) (FPTR(p1)->F_DEV == FPTR(p2)->F_DEV \
-		    && FPTR(p1)->F_INODE == FPTR(p2)->F_INODE)
+static struct hashtable *dev_tbl;
 
-static int hlink_compare(int *int1, int *int2)
+static struct hashtable *prior_hlinks;
+
+static struct file_list *hlink_flist;
+
+void init_hard_links(void)
 {
-	struct file_struct *f1 = FPTR(*int1);
-	struct file_struct *f2 = FPTR(*int2);
+	if (am_sender || protocol_version < 30)
+		dev_tbl = hashtable_create(16, SIZEOF_INT64 == 8);
+	else if (inc_recurse)
+		prior_hlinks = hashtable_create(1024, 0);
+}
 
-	if (f1->F_DEV != f2->F_DEV)
-		return (int) (f1->F_DEV > f2->F_DEV ? 1 : -1);
+struct ht_int64_node *idev_find(int64 dev, int64 ino)
+{
+	static struct ht_int64_node *dev_node = NULL;
+	struct hashtable *tbl;
 
-	if (f1->F_INODE != f2->F_INODE)
-		return (int) (f1->F_INODE > f2->F_INODE ? 1 : -1);
+	if (!dev_node || dev_node->key != dev) {
+		/* We keep a separate hash table of inodes for every device. */
+		dev_node = hashtable_find(dev_tbl, dev, 1);
+		if (!(tbl = dev_node->data))
+			tbl = dev_node->data = hashtable_create(512, SIZEOF_INT64 == 8);
+	} else
+		tbl = dev_node->data;
 
-	return f_name_cmp(f1, f2);
+	return hashtable_find(tbl, ino, 1);
 }
 
-static int32 *hlink_list;
-static int32 hlink_count;
+void idev_destroy(void)
+{
+	int i;
+
+	for (i = 0; i < dev_tbl->size; i++) {
+		struct ht_int32_node *node = HT_NODE(dev_tbl, dev_tbl->nodes, i);
+		if (node->data)
+			hashtable_destroy(node->data);
+	}
+
+	hashtable_destroy(dev_tbl);
+}
 
-/* Analyze the data in the hlink_list[], remove items that aren't multiply
- * linked, and replace the dev+inode data with the hlindex+next linked list. */
-static void link_idev_data(void)
+static int hlink_compare_gnum(int *int1, int *int2)
 {
-	int32 cur, from, to, start;
+	struct file_struct *f1 = hlink_flist->sorted[*int1];
+	struct file_struct *f2 = hlink_flist->sorted[*int2];
+	int32 gnum1 = F_HL_GNUM(f1);
+	int32 gnum2 = F_HL_GNUM(f2);
 
-	alloc_pool_t hlink_pool;
-	alloc_pool_t idev_pool = the_file_list->hlink_pool;
+	if (gnum1 != gnum2)
+		return gnum1 > gnum2 ? 1 : -1;
 
-	hlink_pool = pool_create(128 * 1024, sizeof (struct hlink),
-	    out_of_memory, POOL_INTERN);
+	return *int1 > *int2 ? 1 : -1;
+}
 
-	for (from = to = 0; from < hlink_count; from++) {
-		start = from;
-		while (1) {
-			cur = hlink_list[from];
-			if (from == hlink_count-1
-			    || !LINKED(cur, hlink_list[from+1]))
+static void match_gnums(int32 *ndx_list, int ndx_count)
+{
+	int32 from, prev;
+	struct file_struct *file, *file_next;
+	struct ht_int32_node *node = NULL;
+	int32 gnum, gnum_next;
+
+	qsort(ndx_list, ndx_count, sizeof ndx_list[0],
+	     (int (*)()) hlink_compare_gnum);
+
+	for (from = 0; from < ndx_count; from++) {
+		file = hlink_flist->sorted[ndx_list[from]];
+		gnum = F_HL_GNUM(file);
+		if (inc_recurse) {
+			node = hashtable_find(prior_hlinks, gnum, 1);
+			if (!node->data) {
+				node->data = new_array0(char, 5);
+				assert(gnum >= hlink_flist->ndx_start);
+				file->flags |= FLAG_HLINK_FIRST;
+				prev = -1;
+			} else if (CVAL(node->data, 0) == 0) {
+				struct file_list *flist;
+				struct file_struct *fp;
+				prev = IVAL(node->data, 1);
+				flist = flist_for_ndx(prev);
+				assert(flist != NULL);
+				fp = flist->files[prev - flist->ndx_start];
+				fp->flags &= ~FLAG_HLINK_LAST;
+			} else
+				prev = -1;
+		} else {
+			file->flags |= FLAG_HLINK_FIRST;
+			prev = -1;
+		}
+		for ( ; from < ndx_count-1; file = file_next, gnum = gnum_next, from++) { /*SHARED ITERATOR*/
+			file_next = hlink_flist->sorted[ndx_list[from+1]];
+			gnum_next = F_HL_GNUM(file_next);
+			if (gnum != gnum_next)
 				break;
-			pool_free(idev_pool, 0, FPTR(cur)->link_u.idev);
-			FPTR(cur)->link_u.links = pool_talloc(hlink_pool,
-			    struct hlink, 1, "hlink_list");
-
-			FPTR(cur)->F_HLINDEX = to;
-			FPTR(cur)->F_NEXT = hlink_list[++from];
-			FPTR(cur)->link_u.links->link_dest_used = 0;
-		}
-		pool_free(idev_pool, 0, FPTR(cur)->link_u.idev);
-		if (from > start) {
-			int head = hlink_list[start];
-			FPTR(cur)->link_u.links = pool_talloc(hlink_pool,
-			    struct hlink, 1, "hlink_list");
-
-			FPTR(head)->flags |= FLAG_HLINK_TOL;
-			FPTR(cur)->F_HLINDEX = to;
-			FPTR(cur)->F_NEXT = head;
-			FPTR(cur)->flags |= FLAG_HLINK_EOL;
-			FPTR(cur)->link_u.links->link_dest_used = 0;
-			hlink_list[to++] = head;
-		} else
-			FPTR(cur)->link_u.links = NULL;
-	}
+			F_HL_PREV(file) = prev;
+			/* The linked list uses over-the-wire ndx values. */
+			if (unsort_ndx)
+				prev = F_NDX(file);
+			else
+				prev = ndx_list[from] + hlink_flist->ndx_start;
+		}
+		if (prev < 0 && !inc_recurse) {
+			/* Disable hard-link bit and set DONE so that
+			 * HLINK_BUMP()-dependent values are unaffected. */
+			file->flags &= ~(FLAG_HLINKED | FLAG_HLINK_FIRST);
+			file->flags |= FLAG_HLINK_DONE;
+			continue;
+		}
 
-	if (!to) {
-		free(hlink_list);
-		hlink_list = NULL;
-		pool_destroy(hlink_pool);
-		hlink_pool = NULL;
-	} else {
-		hlink_count = to;
-		hlink_list = realloc_array(hlink_list, int32, hlink_count);
-		if (!hlink_list)
-			out_of_memory("init_hard_links");
+		file->flags |= FLAG_HLINK_LAST;
+		F_HL_PREV(file) = prev;
+		if (inc_recurse && CVAL(node->data, 0) == 0) {
+			if (unsort_ndx)
+				prev = F_NDX(file);
+			else
+				prev = ndx_list[from] + hlink_flist->ndx_start;
+			SIVAL(node->data, 1, prev);
+		}
 	}
-	the_file_list->hlink_pool = hlink_pool;
-	pool_destroy(idev_pool);
 }
-#endif
 
-void init_hard_links(void)
+/* Analyze the hard-links in the file-list by creating a list of all the
+ * items that have hlink data, sorting them, and matching up identical
+ * values into clusters.  These will be a single linked list from last
+ * to first when we're done. */
+void match_hard_links(struct file_list *flist)
 {
-#ifdef SUPPORT_HARD_LINKS
-	int i;
+	if (!list_only) {
+		int i, ndx_count = 0;
+		int32 *ndx_list;
+
+		if (!(ndx_list = new_array(int32, flist->used)))
+			out_of_memory("match_hard_links");
+
+		for (i = 0; i < flist->used; i++) {
+			if (F_IS_HLINKED(flist->sorted[i]))
+				ndx_list[ndx_count++] = i;
+		}
 
-	if (hlink_list)
-		free(hlink_list);
+		hlink_flist = flist;
 
-	if (!(hlink_list = new_array(int32, the_file_list->count)))
-		out_of_memory("init_hard_links");
+		if (ndx_count)
+			match_gnums(ndx_list, ndx_count);
 
-	hlink_count = 0;
-	for (i = 0; i < the_file_list->count; i++) {
-		if (FPTR(i)->link_u.idev)
-			hlink_list[hlink_count++] = i;
+		free(ndx_list);
 	}
-
-	qsort(hlink_list, hlink_count,
-	    sizeof hlink_list[0], (int (*)()) hlink_compare);
-
-	if (!hlink_count) {
-		free(hlink_list);
-		hlink_list = NULL;
-	} else
-		link_idev_data();
-#endif
+	if (protocol_version < 30)
+		idev_destroy();
 }
 
-#ifdef SUPPORT_HARD_LINKS
 static int maybe_hard_link(struct file_struct *file, int ndx,
-			   char *fname, int statret, STRUCT_STAT *st,
-			   char *toname, STRUCT_STAT *to_st,
-			   int itemizing, enum logcode code)
+			   const char *fname, int statret, stat_x *sxp,
+			   const char *oldname, STRUCT_STAT *old_stp,
+			   const char *realname, int itemizing, enum logcode code)
 {
 	if (statret == 0) {
-		if (st->st_dev == to_st->st_dev
-		 && st->st_ino == to_st->st_ino) {
+		if (sxp->st.st_dev == old_stp->st_dev
+		 && sxp->st.st_ino == old_stp->st_ino) {
 			if (itemizing) {
-				itemize(file, ndx, statret, st,
+				itemize(fname, file, ndx, statret, sxp,
 					ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS,
 					0, "");
 			}
+			if (verbose > 1 && maybe_ATTRS_REPORT)
+				rprintf(FCLIENT, "%s is uptodate\n", fname);
+			file->flags |= FLAG_HLINK_DONE;
 			return 0;
 		}
-		if (make_backups) {
+		if (make_backups > 0) {
 			if (!make_backup(fname))
 				return -1;
 		} else if (robust_unlink(fname)) {
-			rsyserr(FERROR, errno, "unlink %s failed",
+			rsyserr(FERROR_XFER, errno, "unlink %s failed",
 				full_fname(fname));
 			return -1;
 		}
 	}
-	return hard_link_one(file, ndx, fname, statret, st, toname,
-			     0, itemizing, code);
+
+	if (hard_link_one(file, fname, oldname, 0)) {
+		if (itemizing) {
+			itemize(fname, file, ndx, statret, sxp,
+				ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS, 0,
+				realname);
+		}
+		if (code != FNONE && verbose)
+			rprintf(code, "%s => %s\n", fname, realname);
+		return 0;
+	}
+	return -1;
 }
-#endif
 
-int hard_link_check(struct file_struct *file, int ndx, char *fname,
-		    int statret, STRUCT_STAT *st, int itemizing,
-		    enum logcode code, int skip)
+/* Figure out if a prior entry is still there or if we just have a
+ * cached name for it.  Never called with a FLAG_HLINK_FIRST entry. */
+static char *check_prior(int prev_ndx, int gnum, struct file_list **flist_p)
 {
-#ifdef SUPPORT_HARD_LINKS
-	int head;
-	if (skip && !(file->flags & FLAG_HLINK_EOL))
-		head = hlink_list[file->F_HLINDEX] = file->F_NEXT;
-	else
-		head = hlink_list[file->F_HLINDEX];
-	if (ndx != head) {
-		struct file_struct *head_file = FPTR(head);
-		if (!stdout_format_has_i && verbose > 1) {
-			rprintf(FINFO, "\"%s\" is a hard link\n",
-				f_name(file, NULL));
-		}
-		if (head_file->F_HLINDEX == FINISHED_LINK) {
-			STRUCT_STAT st2, st3;
-			char toname[MAXPATHLEN];
-			int ldu = head_file->link_u.links->link_dest_used;
-			if (ldu) {
-				pathjoin(toname, MAXPATHLEN, basis_dir[ldu-1],
-					 f_name(head_file, NULL));
-			} else
-				f_name(head_file, toname);
-			if (link_stat(toname, &st2, 0) < 0) {
-				rsyserr(FERROR, errno, "stat %s failed",
-					full_fname(toname));
-				return -1;
-			}
-			if (statret < 0 && basis_dir[0] != NULL) {
-				char cmpbuf[MAXPATHLEN];
-				int j = 0;
-				do {
-					pathjoin(cmpbuf, MAXPATHLEN, basis_dir[j], fname);
-					if (link_stat(cmpbuf, &st3, 0) < 0)
-						continue;
-					if (link_dest) {
-						if (st2.st_dev != st3.st_dev
-						 || st2.st_ino != st3.st_ino)
-							continue;
-						statret = 1;
-						st = &st3;
-						if (verbose < 2 || !stdout_format_has_i) {
-							itemizing = 0;
-							code = FNONE;
-						}
-						break;
-					}
-					if (!unchanged_file(cmpbuf, file, &st3))
-						continue;
-					statret = 1;
-					st = &st3;
-					if (unchanged_attrs(file, &st3))
-						break;
-				} while (basis_dir[++j] != NULL);
+	struct file_list *flist = flist_for_ndx(prev_ndx);
+	struct ht_int32_node *node;
+
+	if (flist) {
+		*flist_p = flist;
+		return NULL;
+	}
+
+	node = hashtable_find(prior_hlinks, gnum, 0);
+	assert(node != NULL && node->data);
+	assert(CVAL(node->data, 0) != 0);
+	return node->data;
+}
+
+/* Only called if FLAG_HLINKED is set and FLAG_HLINK_FIRST is not.  Returns:
+ * 0 = process the file, 1 = skip the file, -1 = error occurred. */
+int hard_link_check(struct file_struct *file, int ndx, const char *fname,
+		    int statret, stat_x *sxp, int itemizing,
+		    enum logcode code)
+{
+	STRUCT_STAT prev_st;
+	char namebuf[MAXPATHLEN], altbuf[MAXPATHLEN];
+	char *realname, *prev_name;
+	struct file_list *flist;
+	int gnum = inc_recurse ? F_HL_GNUM(file) : -1;
+	int prev_ndx = F_HL_PREV(file);
+
+	prev_name = realname = check_prior(prev_ndx, gnum, &flist);
+
+	if (!prev_name) {
+		struct file_struct *prev_file = flist->files[prev_ndx - flist->ndx_start];
+
+		/* Is the previous link not complete yet? */
+		if (!(prev_file->flags & FLAG_HLINK_DONE)) {
+			/* Is the previous link being transferred? */
+			if (prev_file->flags & FLAG_FILE_SENT) {
+				/* Add ourselves to the list of files that will
+				 * be updated when the transfer completes, and
+				 * mark ourself as waiting for the transfer. */
+				F_HL_PREV(file) = F_HL_PREV(prev_file);
+				F_HL_PREV(prev_file) = ndx;
+				file->flags |= FLAG_FILE_SENT;
+				cur_flist->in_progress++;
+				return 1;
 			}
-			maybe_hard_link(file, ndx, fname, statret, st,
-					toname, &st2, itemizing, code);
-			if (remove_source_files == 1 && do_xfers) {
-				char numbuf[4];
-				SIVAL(numbuf, 0, ndx);
-				send_msg(MSG_SUCCESS, numbuf, 4);
+			return 0;
+		}
+
+		/* There is a finished file to link with! */
+		if (!(prev_file->flags & FLAG_HLINK_FIRST)) {
+			/* The previous previous is FIRST when prev is not. */
+			prev_ndx = F_HL_PREV(prev_file);
+			prev_name = realname = check_prior(prev_ndx, gnum, &flist);
+			/* Update our previous pointer to point to the FIRST. */
+			F_HL_PREV(file) = prev_ndx;
+		}
+
+		if (!prev_name) {
+			int alt_dest;
+
+			prev_file = flist->files[prev_ndx - flist->ndx_start];
+			/* F_HL_PREV() is alt_dest value when DONE && FIRST. */
+			alt_dest = F_HL_PREV(prev_file);
+
+			if (alt_dest >= 0 && dry_run) {
+				pathjoin(namebuf, MAXPATHLEN, basis_dir[alt_dest],
+					 f_name(prev_file, NULL));
+				prev_name = namebuf;
+				realname = f_name(prev_file, altbuf);
+			} else {
+				prev_name = f_name(prev_file, namebuf);
+				realname = prev_name;
 			}
-			file->F_HLINDEX = FINISHED_LINK;
-		} else
-			file->F_HLINDEX = SKIPPED_LINK;
-		return 1;
+		}
+	}
+
+	if (link_stat(prev_name, &prev_st, 0) < 0) {
+		rsyserr(FERROR_XFER, errno, "stat %s failed",
+			full_fname(prev_name));
+		return -1;
 	}
+
+	if (statret < 0 && basis_dir[0] != NULL) {
+		/* If we match an alt-dest item, we don't output this as a change. */
+		char cmpbuf[MAXPATHLEN];
+		stat_x alt_sx;
+		int j = 0;
+#ifdef SUPPORT_ACLS
+		alt_sx.acc_acl = alt_sx.def_acl = NULL;
+#endif
+		do {
+			pathjoin(cmpbuf, MAXPATHLEN, basis_dir[j], fname);
+			if (link_stat(cmpbuf, &alt_sx.st, 0) < 0)
+				continue;
+			if (link_dest) {
+				if (prev_st.st_dev != alt_sx.st.st_dev
+				 || prev_st.st_ino != alt_sx.st.st_ino)
+					continue;
+				statret = 1;
+				if (stdout_format_has_i == 0
+				 || (verbose < 2 && stdout_format_has_i < 2)) {
+					itemizing = 0;
+					code = FNONE;
+					if (verbose > 1 && maybe_ATTRS_REPORT)
+						rprintf(FCLIENT, "%s is uptodate\n", fname);
+				}
+				break;
+			}
+			if (!unchanged_file(cmpbuf, file, &alt_sx.st))
+				continue;
+			statret = 1;
+			if (unchanged_attrs(cmpbuf, file, &alt_sx))
+				break;
+		} while (basis_dir[++j] != NULL);
+		if (statret == 1) {
+			sxp->st = alt_sx.st;
+#ifdef SUPPORT_ACLS
+			if (preserve_acls && !S_ISLNK(file->mode)) {
+				if (!ACL_READY(*sxp))
+					get_acl(cmpbuf, sxp);
+				else {
+					sxp->acc_acl = alt_sx.acc_acl;
+					sxp->def_acl = alt_sx.def_acl;
+				}
+			}
 #endif
-	return 0;
+		}
+#ifdef SUPPORT_ACLS
+		else if (preserve_acls)
+			free_acl(&alt_sx);
+#endif
+	}
+
+	if (maybe_hard_link(file, ndx, fname, statret, sxp, prev_name, &prev_st,
+			    realname, itemizing, code) < 0)
+		return -1;
+
+	if (remove_source_files == 1 && do_xfers)
+		send_msg_int(MSG_SUCCESS, ndx);
+
+	return 1;
 }
 
-#ifdef SUPPORT_HARD_LINKS
-int hard_link_one(struct file_struct *file, int ndx, char *fname,
-		  int statret, STRUCT_STAT *st, char *toname, int terse,
-		  int itemizing, enum logcode code)
+int hard_link_one(struct file_struct *file, const char *fname,
+		  const char *oldname, int terse)
 {
-	if (do_link(toname, fname)) {
+	if (do_link(oldname, fname) < 0) {
+		enum logcode code;
 		if (terse) {
 			if (!verbose)
-				return -1;
+				return 0;
 			code = FINFO;
 		} else
-			code = FERROR;
+			code = FERROR_XFER;
 		rsyserr(code, errno, "link %s => %s failed",
-			full_fname(fname), toname);
-		return -1;
+			full_fname(fname), oldname);
+		return 0;
 	}
 
-	if (itemizing) {
-		itemize(file, ndx, statret, st,
-			ITEM_LOCAL_CHANGE | ITEM_XNAME_FOLLOWS, 0,
-			terse ? "" : toname);
-	}
-	if (code != FNONE && verbose && !terse)
-		rprintf(code, "%s => %s\n", fname, toname);
-	return 0;
-}
-#endif
+	file->flags |= FLAG_HLINK_DONE;
 
+	return 1;
+}
 
-void hard_link_cluster(struct file_struct *file, int master, int itemizing,
-		       enum logcode code)
+void finish_hard_link(struct file_struct *file, const char *fname, int fin_ndx,
+		      STRUCT_STAT *stp, int itemizing, enum logcode code,
+		      int alt_dest)
 {
-#ifdef SUPPORT_HARD_LINKS
-	char hlink1[MAXPATHLEN];
-	char *hlink2;
-	STRUCT_STAT st1, st2;
-	int statret, ndx = master;
-
-	file->F_HLINDEX = FINISHED_LINK;
-	if (link_stat(f_name(file, hlink1), &st1, 0) < 0)
-		return;
-	if (!(file->flags & FLAG_HLINK_TOL)) {
-		while (!(file->flags & FLAG_HLINK_EOL)) {
-			ndx = file->F_NEXT;
-			file = FPTR(ndx);
-		}
-	}
-	do {
-		ndx = file->F_NEXT;
-		file = FPTR(ndx);
-		if (file->F_HLINDEX != SKIPPED_LINK)
-			continue;
-		hlink2 = f_name(file, NULL);
-		statret = link_stat(hlink2, &st2, 0);
-		maybe_hard_link(file, ndx, hlink2, statret, &st2,
-				hlink1, &st1, itemizing, code);
-		if (remove_source_files == 1 && do_xfers) {
-			char numbuf[4];
-			SIVAL(numbuf, 0, ndx);
-			send_msg(MSG_SUCCESS, numbuf, 4);
+	stat_x prev_sx;
+	STRUCT_STAT st;
+	char alt_name[MAXPATHLEN], *prev_name;
+	const char *our_name;
+	struct file_list *flist;
+	int prev_statret, ndx, prev_ndx = F_HL_PREV(file);
+
+	if (stp == NULL && prev_ndx >= 0) {
+		if (link_stat(fname, &st, 0) < 0) {
+			rsyserr(FERROR_XFER, errno, "stat %s failed",
+				full_fname(fname));
+			return;
 		}
-		file->F_HLINDEX = FINISHED_LINK;
-	} while (!(file->flags & FLAG_HLINK_EOL));
+		stp = &st;
+	}
+
+	/* FIRST combined with DONE means we were the first to get done. */
+	file->flags |= FLAG_HLINK_FIRST | FLAG_HLINK_DONE;
+	F_HL_PREV(file) = alt_dest;
+	if (alt_dest >= 0 && dry_run) {
+		pathjoin(alt_name, MAXPATHLEN, basis_dir[alt_dest],
+			 f_name(file, NULL));
+		our_name = alt_name;
+	} else
+		our_name = fname;
+
+#ifdef SUPPORT_ACLS
+	prev_sx.acc_acl = prev_sx.def_acl = NULL;
+#endif
+
+	while ((ndx = prev_ndx) >= 0) {
+		int val;
+		flist = flist_for_ndx(ndx);
+		assert(flist != NULL);
+		file = flist->files[ndx - flist->ndx_start];
+		file->flags = (file->flags & ~FLAG_HLINK_FIRST) | FLAG_HLINK_DONE;
+		prev_ndx = F_HL_PREV(file);
+		F_HL_PREV(file) = fin_ndx;
+		prev_name = f_name(file, NULL);
+		prev_statret = link_stat(prev_name, &prev_sx.st, 0);
+		val = maybe_hard_link(file, ndx, prev_name, prev_statret, &prev_sx,
+				      our_name, stp, fname, itemizing, code);
+		flist->in_progress--;
+#ifdef SUPPORT_ACLS
+		if (preserve_acls)
+			free_acl(&prev_sx);
 #endif
+		if (val < 0)
+			continue;
+		if (remove_source_files == 1 && do_xfers)
+			send_msg_int(MSG_SUCCESS, ndx);
+	}
+
+	if (inc_recurse) {
+		int gnum = F_HL_GNUM(file);
+		struct ht_int32_node *node = hashtable_find(prior_hlinks, gnum, 0);
+		assert(node != NULL && node->data != NULL);
+		assert(CVAL(node->data, 0) == 0);
+		free(node->data);
+		if (!(node->data = strdup(our_name)))
+			out_of_memory("finish_hard_link");
+	}
 }
+#endif
