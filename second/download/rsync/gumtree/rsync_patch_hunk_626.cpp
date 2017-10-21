 
 extern int verbose;
 extern int delete_mode;
 
 static struct exclude_struct **exclude_list;
 
-/* build an exclude structure given a exclude pattern */
+/** Build an exclude structure given a exclude pattern */
 static struct exclude_struct *make_exclude(const char *pattern, int include)
 {
 	struct exclude_struct *ret;
 
 	ret = (struct exclude_struct *)malloc(sizeof(*ret));
 	if (!ret) out_of_memory("make_exclude");
