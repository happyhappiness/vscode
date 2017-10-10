 	printf("%s=%d\n", var, val);
 }
 
 static int show_bisect_vars(struct rev_list_info *info, int reaches, int all)
 {
 	int cnt, flags = info->flags;
-	char hex[41] = "";
+	char hex[GIT_SHA1_HEXSZ + 1] = "";
 	struct commit_list *tried;
 	struct rev_info *revs = info->revs;
 
 	if (!revs->commits)
 		return 1;
 
