 	int slop = SLOP;
 	unsigned long date = ~0ul;
 	struct commit_list *list = revs->commits;
 	struct commit_list *newlist = NULL;
 	struct commit_list **p = &newlist;
 	struct commit_list *bottom = NULL;
+	struct commit *interesting_cache = NULL;
 
 	if (revs->ancestry_path) {
 		bottom = collect_bottom_commits(list);
 		if (!bottom)
 			die("--ancestry-path given but there are no bottom commits");
 	}
