 {
 	fprintf(stderr, "exit(%d): %s(%d)\n",
 		code, file, line);
 	exit(code);
 }
 
- int check_filter(UNUSED(struct filter_list_struct *listp), UNUSED(char *name),
-		   UNUSED(int name_is_dir))
+ int check_filter(UNUSED(struct filter_list_struct *listp), UNUSED(enum logcode code),
+		  UNUSED(const char *name), UNUSED(int name_is_dir))
 {
 	/* This function doesn't really get called in this test context, so
 	 * just return 0. */
 	return 0;
 }
 
