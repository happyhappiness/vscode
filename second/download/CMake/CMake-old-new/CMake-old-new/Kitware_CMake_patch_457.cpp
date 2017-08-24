@@ -6619,7 +6619,7 @@ isoent_collect_dirs(struct vdd *vdd, struct isoent *rootent, int depth)
  */
 static int
 isoent_rr_move_dir(struct archive_write *a, struct isoent **rr_moved,
-    struct isoent *isoent, struct isoent **newent)
+    struct isoent *curent, struct isoent **newent)
 {
 	struct iso9660 *iso9660 = a->format_data;
 	struct isoent *rrmoved, *mvent, *np;
@@ -6645,40 +6645,40 @@ isoent_rr_move_dir(struct archive_write *a, struct isoent **rr_moved,
 		*rr_moved = rrmoved;
 	}
 	/*
-	 * Make a clone of isoent which is going to be relocated
+	 * Make a clone of curent which is going to be relocated
 	 * to rr_moved.
 	 */
-	mvent = isoent_clone(isoent);
+	mvent = isoent_clone(curent);
 	if (mvent == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate memory");
 		return (ARCHIVE_FATAL);
 	}
 	/* linking..  and use for creating "CL", "PL" and "RE" */
-	mvent->rr_parent = isoent->parent;
-	isoent->rr_child = mvent;
+	mvent->rr_parent = curent->parent;
+	curent->rr_child = mvent;
 	/*
-	 * Move subdirectories from the isoent to mvent
+	 * Move subdirectories from the curent to mvent
 	 */
-	if (isoent->children.first != NULL) {
-		*mvent->children.last = isoent->children.first;
-		mvent->children.last = isoent->children.last;
+	if (curent->children.first != NULL) {
+		*mvent->children.last = curent->children.first;
+		mvent->children.last = curent->children.last;
 	}
 	for (np = mvent->children.first; np != NULL; np = np->chnext)
 		np->parent = mvent;
-	mvent->children.cnt = isoent->children.cnt;
-	isoent->children.cnt = 0;
-	isoent->children.first = NULL;
-	isoent->children.last = &isoent->children.first;
+	mvent->children.cnt = curent->children.cnt;
+	curent->children.cnt = 0;
+	curent->children.first = NULL;
+	curent->children.last = &curent->children.first;
 
-	if (isoent->subdirs.first != NULL) {
-		*mvent->subdirs.last = isoent->subdirs.first;
-		mvent->subdirs.last = isoent->subdirs.last;
+	if (curent->subdirs.first != NULL) {
+		*mvent->subdirs.last = curent->subdirs.first;
+		mvent->subdirs.last = curent->subdirs.last;
 	}
-	mvent->subdirs.cnt = isoent->subdirs.cnt;
-	isoent->subdirs.cnt = 0;
-	isoent->subdirs.first = NULL;
-	isoent->subdirs.last = &isoent->subdirs.first;
+	mvent->subdirs.cnt = curent->subdirs.cnt;
+	curent->subdirs.cnt = 0;
+	curent->subdirs.first = NULL;
+	curent->subdirs.last = &curent->subdirs.first;
 
 	/*
 	 * The mvent becomes a child of the rr_moved entry.
@@ -6691,7 +6691,7 @@ isoent_rr_move_dir(struct archive_write *a, struct isoent **rr_moved,
 	 * has to set the flag as a file.
 	 * See also RRIP 4.1.5.1 Description of the "CL" System Use Entry.
 	 */
-	isoent->dir = 0;
+	curent->dir = 0;
 
 	*newent = mvent;
 