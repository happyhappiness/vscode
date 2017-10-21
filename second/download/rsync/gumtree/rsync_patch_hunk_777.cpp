 oom:
 	out_of_memory("recv_file_list");
 	return NULL;		/* not reached */
 }
 
 
-int file_compare(struct file_struct **file1, struct file_struct **file2)
+static int file_compare(struct file_struct **file1, struct file_struct **file2)
 {
-	struct file_struct *f1 = *file1;
-	struct file_struct *f2 = *file2;
-
-	if (!f1->basename && !f2->basename)
-		return 0;
-	if (!f1->basename)
-		return -1;
-	if (!f2->basename)
-		return 1;
-	if (f1->dirname == f2->dirname)
-		return u_strcmp(f1->basename, f2->basename);
-	return f_name_cmp(f1, f2);
+	return f_name_cmp(*file1, *file2);
 }
 
 
+/* Search for an identically-named item in the file list.  Note that the
+ * items must agree in their directory-ness, or no match is returned. */
 int flist_find(struct file_list *flist, struct file_struct *f)
 {
-	int low = 0, high = flist->count - 1;
-
-	while (high >= 0 && !flist->files[high]->basename) high--;
+	int low = flist->low, high = flist->high;
+	int ret, mid, mid_up;
 
-	if (high < 0)
-		return -1;
-
-	while (low != high) {
-		int mid = (low + high) / 2;
-		int ret = file_compare(&flist->files[flist_up(flist, mid)],&f);
-		if (ret == 0)
-			return flist_up(flist, mid);
+	while (low <= high) {
+		mid = (low + high) / 2;
+		for (mid_up = mid; !flist->files[mid_up]->basename; mid_up++) {}
+		if (mid_up <= high)
+			ret = f_name_cmp(flist->files[mid_up], f);
+		else
+			ret = 1;
+		if (ret == 0) {
+			if (protocol_version < 29
+			    && S_ISDIR(flist->files[mid_up]->mode)
+			    != S_ISDIR(f->mode))
+				return -1;
+			return mid_up;
+		}
 		if (ret > 0)
-			high = mid;
+			high = mid - 1;
 		else
-			low = mid + 1;
+			low = mid_up + 1;
 	}
-
-	if (file_compare(&flist->files[flist_up(flist, low)], &f) == 0)
-		return flist_up(flist, low);
 	return -1;
 }
 
+
 /*
  * Free up any resources a file_struct has allocated
  * and clear the file.
  */
 void clear_file(int i, struct file_list *flist)
 {
