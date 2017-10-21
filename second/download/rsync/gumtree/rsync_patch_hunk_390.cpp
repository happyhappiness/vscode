       fprintf(FINFO,"deleting directory %s\n",f_name(f));      
     }
   }
 }
 
 
-/* yuck! This function wouldn't have been necessary if I had the sorting
-   algorithm right. Unfortunately fixing the sorting algorithm would introduce
-   a backward incompatibility as file list indexes are sent over the link.
-
-   The aim is to see if a directory has already had the deletion algorithm applied
-   to it (due to recursion), and if so to skip it. The bisection is to 
-   prevent this being an n^2 algorithm */
-static int delete_already_done(struct file_list *flist,int j)
-{
-	int low=0,high=j-1;
-	char *name;
-	char *p;
-
-	if (j == 0) return 0;
 
-	name = strdup(f_name(flist->files[j]));
+static struct delete_list {
+	dev_t dev;
+	ino_t inode;
+} *delete_list;
+static int dlist_len, dlist_alloc_len;
 
-	if (!name) {
-		fprintf(FERROR,"out of memory in delete_already_done");
-		exit_cleanup(1);
+static void add_delete_entry(struct file_struct *file)
+{
+	if (dlist_len == dlist_alloc_len) {
+		dlist_alloc_len += 1024;
+		if (!delete_list) {
+			delete_list = (struct delete_list *)malloc(sizeof(delete_list[0])*dlist_alloc_len);
+		} else {
+			delete_list = (struct delete_list *)realloc(delete_list, sizeof(delete_list[0])*dlist_alloc_len);
+		}
+		if (!delete_list) out_of_memory("add_delete_entry");
 	}
 
-	name[strlen(name)-2] = 0;
+	delete_list[dlist_len].dev = file->dev;
+	delete_list[dlist_len].inode = file->inode;
+	dlist_len++;
 
-	p = strrchr(name,'/');
-	if (!p) {
-		free(name);
-		return 0;
-	}
-	*p = 0;
-
-	strcat(name,"/.");
+	if (verbose > 3)
+		fprintf(FINFO,"added %s to delete list\n", f_name(file));
+}
 
-	while (low != high) {
-		int mid = (low+high)/2;
-		int ret = strcmp(f_name(flist->files[flist_up(flist, mid)]),name);
-		if (ret == 0) {
-			free(name);
-			return 1;
-		}
-		if (ret > 0) {
-			high=mid;
-		} else {
-			low=mid+1;
-		}
-	}
+/* yuck! This function wouldn't have been necessary if I had the sorting
+   algorithm right. Unfortunately fixing the sorting algorithm would introduce
+   a backward incompatibility as file list indexes are sent over the link.
+*/
+static int delete_already_done(struct file_list *flist,int j)
+{
+	int i;
+	struct stat st;
 
-	low = flist_up(flist, low);
+	if (link_stat(f_name(flist->files[j]), &st)) return 1;
 
-	if (strcmp(f_name(flist->files[low]),name) == 0) {
-		free(name);
-		return 1;
+	for (i=0;i<dlist_len;i++) {
+		if (st.st_ino == delete_list[i].inode &&
+		    st.st_dev == delete_list[i].dev)
+			return 1;
 	}
 
-	free(name);
 	return 0;
 }
 
 
 /* this deletes any files on the receiving side that are not present
    on the sending side. For version 1.6.4 I have changed the behaviour
    to match more closely what most people seem to expect of this option */
 static void delete_files(struct file_list *flist)
 {
-  struct file_list *local_file_list;
-  int i, j;
-
-  if (cvs_exclude)
-    add_cvs_excludes();
+	struct file_list *local_file_list;
+	int i, j;
+	char *name;
 
-  if (io_error) {
-	  fprintf(FINFO,"IO error encountered - skipping file deletion\n");
-	  return;
-  }
+	if (cvs_exclude)
+		add_cvs_excludes();
 
-  for (j=0;j<flist->count;j++) {
-	  char *name = f_name(flist->files[j]);
+	if (io_error) {
+		fprintf(FINFO,"IO error encountered - skipping file deletion\n");
+		return;
+	}
 
-	  if (!S_ISDIR(flist->files[j]->mode)) continue;
+	for (j=0;j<flist->count;j++) {
+		if (!S_ISDIR(flist->files[j]->mode) || 
+		    !(flist->files[j]->flags & FLAG_DELETE)) continue;
 
-	  if (strlen(name)<2 || strcmp(name+strlen(name)-2,"/.")!=0) continue;
+		if (delete_already_done(flist, j)) continue;
 
-	  if (delete_already_done(flist, j)) continue;
+		name = strdup(f_name(flist->files[j]));
 
-	  if (!(local_file_list = send_file_list(-1,1,&name)))
-		  continue;
+		if (!(local_file_list = send_file_list(-1,1,&name))) {
+			free(name);
+			continue;
+		}
 
-	  if (verbose > 1)
-		  fprintf(FINFO,"deleting in %s\n", name);
+		if (verbose > 1)
+			fprintf(FINFO,"deleting in %s\n", name);
 
-	  for (i=local_file_list->count-1;i>=0;i--) {
-		  if (!local_file_list->files[i]->basename) continue;
-		  if (-1 == flist_find(flist,local_file_list->files[i])) {
-			  delete_one(local_file_list->files[i]);
-		  }    
-	  }
-	  flist_free(local_file_list);
-  }
+		for (i=local_file_list->count-1;i>=0;i--) {
+			if (!local_file_list->files[i]->basename) continue;
+			if (S_ISDIR(local_file_list->files[i]->mode))
+				add_delete_entry(local_file_list->files[i]);
+			if (-1 == flist_find(flist,local_file_list->files[i])) {
+				delete_one(local_file_list->files[i]);
+			}    
+		}
+		flist_free(local_file_list);
+		free(name);
+	}
 }
 
 static char *cleanup_fname;
 
 void exit_cleanup(int code)
 {
