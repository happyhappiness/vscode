 	int low=0,high=j-1;
 	char *name;
 	char *p;
 
 	if (j == 0) return 0;
 
-	name = strdup(flist->files[j].name);
+	name = strdup(f_name(flist->files[j]));
 
 	if (!name) {
 		fprintf(FERROR,"out of memory in delete_already_done");
 		exit_cleanup(1);
 	}
 
