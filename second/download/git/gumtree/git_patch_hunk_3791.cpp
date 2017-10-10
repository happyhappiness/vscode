 			return retval;
 	}
 	return 0;
 }
 
 /*
- * Call fn for each reference in the union of dir1 and dir2, in order
- * by refname.  Recurse into subdirectories.  If a value entry appears
- * in both dir1 and dir2, then only process the version that is in
- * dir2.  The input dirs must already be sorted, but subdirs will be
- * sorted as needed.  fn is called for all references, including
- * broken ones.
- */
-static int do_for_each_entry_in_dirs(struct ref_dir *dir1,
-				     struct ref_dir *dir2,
-				     each_ref_entry_fn fn, void *cb_data)
-{
-	int retval;
-	int i1 = 0, i2 = 0;
-
-	assert(dir1->sorted == dir1->nr);
-	assert(dir2->sorted == dir2->nr);
-	while (1) {
-		struct ref_entry *e1, *e2;
-		int cmp;
-		if (i1 == dir1->nr) {
-			return do_for_each_entry_in_dir(dir2, i2, fn, cb_data);
-		}
-		if (i2 == dir2->nr) {
-			return do_for_each_entry_in_dir(dir1, i1, fn, cb_data);
-		}
-		e1 = dir1->entries[i1];
-		e2 = dir2->entries[i2];
-		cmp = strcmp(e1->name, e2->name);
-		if (cmp == 0) {
-			if ((e1->flag & REF_DIR) && (e2->flag & REF_DIR)) {
-				/* Both are directories; descend them in parallel. */
-				struct ref_dir *subdir1 = get_ref_dir(e1);
-				struct ref_dir *subdir2 = get_ref_dir(e2);
-				sort_ref_dir(subdir1);
-				sort_ref_dir(subdir2);
-				retval = do_for_each_entry_in_dirs(
-						subdir1, subdir2, fn, cb_data);
-				i1++;
-				i2++;
-			} else if (!(e1->flag & REF_DIR) && !(e2->flag & REF_DIR)) {
-				/* Both are references; ignore the one from dir1. */
-				retval = fn(e2, cb_data);
-				i1++;
-				i2++;
-			} else {
-				die("conflict between reference and directory: %s",
-				    e1->name);
-			}
-		} else {
-			struct ref_entry *e;
-			if (cmp < 0) {
-				e = e1;
-				i1++;
-			} else {
-				e = e2;
-				i2++;
-			}
-			if (e->flag & REF_DIR) {
-				struct ref_dir *subdir = get_ref_dir(e);
-				sort_ref_dir(subdir);
-				retval = do_for_each_entry_in_dir(
-						subdir, 0, fn, cb_data);
-			} else {
-				retval = fn(e, cb_data);
-			}
-		}
-		if (retval)
-			return retval;
-	}
-}
-
-/*
  * Load all of the refs from the dir into our in-memory cache. The hard work
  * of loading loose refs is done by get_ref_dir(), so we just need to recurse
  * through all of the sub-directories. We do not even need to care about
  * sorting, as traversal order does not matter to us.
  */
 static void prime_ref_dir(struct ref_dir *dir)
