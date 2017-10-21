 
 	if (file_compare(&flist->files[flist_up(flist, low)], &f) == 0)
 		return flist_up(flist, low);
 	return -1;
 }
 
-
 /*
- * free up one file
+ * Free up any resources a file_struct has allocated
+ * and clear the file.
  */
-void free_file(struct file_struct *file)
+void clear_file(int i, struct file_list *flist)
 {
-	if (!file)
-		return;
-	if (file->basename)
-		free(file->basename);
-	if (file->link)
-		free(file->link);
-	if (file->sum)
-		free(file->sum);
-	*file = null_file;
+	if (flist->hlink_pool && flist->files[i]->link_u.idev)
+		pool_free(flist->hlink_pool, 0, flist->files[i]->link_u.idev);
+	memset(flist->files[i], 0, file_struct_len);
 }
 
 
 /*
  * allocate a new file list
  */
-struct file_list *flist_new(void)
+struct file_list *flist_new(int with_hlink, char *msg)
 {
 	struct file_list *flist;
 
 	flist = new(struct file_list);
 	if (!flist)
-		out_of_memory("send_file_list");
+		out_of_memory(msg);
 
-	flist->count = 0;
-	flist->malloced = 0;
-	flist->files = NULL;
+	memset(flist, 0, sizeof (struct file_list));
 
-#if ARENA_SIZE > 0
-	flist->string_area = string_area_new(0);
-#else
-	flist->string_area = NULL;
+	if (!(flist->file_pool = pool_create(FILE_EXTENT, 0,
+	    out_of_memory, POOL_INTERN)))
+		out_of_memory(msg);
+
+#if SUPPORT_HARD_LINKS
+	if (with_hlink && preserve_hard_links) {
+		if (!(flist->hlink_pool = pool_create(HLINK_EXTENT,
+		    sizeof (struct idev), out_of_memory, POOL_INTERN)))
+			out_of_memory(msg);
+	}
 #endif
+
 	return flist;
 }
 
 /*
  * free up all elements in a flist
  */
