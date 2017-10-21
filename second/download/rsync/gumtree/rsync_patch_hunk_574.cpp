 void free_file(struct file_struct *file)
 {
 	if (!file) return;
 	if (file->basename) free(file->basename);
 	if (file->link) free(file->link);
 	if (file->sum) free(file->sum);
-	memset((char *)file, 0, sizeof(*file));
+	*file = null_file;
 }
 
 
 /*
+ * allocate a new file list
+ */
+struct file_list *flist_new()
+{
+	struct file_list *flist;
+
+	flist = (struct file_list *)malloc(sizeof(flist[0]));
+	if (!flist) out_of_memory("send_file_list");
+
+	flist->count=0;
+	flist->malloced = 1000;
+	flist->files = (struct file_struct **)malloc(sizeof(flist->files[0])*
+						     flist->malloced);
+	if (!flist->files) out_of_memory("send_file_list");
+#if ARENA_SIZE > 0
+	flist->string_area = string_area_new(0);
+#else
+	flist->string_area = 0;
+#endif
+	return flist;
+}
+/*
  * free up all elements in a flist
  */
 void flist_free(struct file_list *flist)
 {
 	int i;
 	for (i=1;i<flist->count;i++) {
-		free_file(flist->files[i]);
+		if (!flist->string_area)
+			free_file(flist->files[i]);
 		free(flist->files[i]);
 	}	
 	memset((char *)flist->files, 0, sizeof(flist->files[0])*flist->count);
 	free(flist->files);
+	if (flist->string_area)
+		string_area_free(flist->string_area);
 	memset((char *)flist, 0, sizeof(*flist));
 	free(flist);
 }
 
 
 /*
