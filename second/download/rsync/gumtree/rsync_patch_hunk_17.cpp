 oom:
   out_of_memory("do_cmd");
   return 0; /* not reached */
 }
 
 
+
+
+static char *get_local_name(struct file_list *flist,char *name)
+{
+  struct stat st;
+
+  if (stat(name,&st) == 0) {
+    if (S_ISDIR(st.st_mode)) {
+      if (chdir(name) != 0) {
+	fprintf(stderr,"chdir %s : %s\n",name,strerror(errno));
+	exit(1);
+      }
+      return NULL;
+    }
+    if (flist->count > 1) {
+      fprintf(stderr,"ERROR: destination must be a diirectory when copying more than 1 file\n");
+      exit(1);
+    }
+    return name;
+  }
+
+  if (flist->count == 1)
+    return name;
+
+  if (mkdir(name,0777) != 0) {
+    fprintf(stderr,"mkdir %s : %s\n",name,strerror(errno));
+    exit(1);
+  }
+
+  if (chdir(name) != 0) {
+    fprintf(stderr,"chdir %s : %s\n",name,strerror(errno));
+    exit(1);
+  }
+
+  return NULL;
+}
+
+
+
+
 void do_server_sender(int argc,char *argv[])
 {
   int i;
   char *dir = argv[0];
   struct file_list *flist;
 
