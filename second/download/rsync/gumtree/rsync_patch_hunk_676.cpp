 
 /* include/exclude cluestick added by Martin Pool <mbp@samba.org> */
 
 #include "rsync.h"
 
 extern int verbose;
-extern int delete_mode;
 
-static struct exclude_struct **exclude_list;
+struct exclude_struct **exclude_list;
+struct exclude_struct **local_exclude_list;
+struct exclude_struct **server_exclude_list;
+char *exclude_path_prefix = NULL;
 
 /** Build an exclude structure given a exclude pattern */
 static struct exclude_struct *make_exclude(const char *pattern, int include)
 {
 	struct exclude_struct *ret;
+	char *cp;
+	int pat_len;
 
 	ret = new(struct exclude_struct);
 	if (!ret) out_of_memory("make_exclude");
 
 	memset(ret, 0, sizeof(*ret));
 
