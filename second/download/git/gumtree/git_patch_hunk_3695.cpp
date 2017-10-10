 		if (bisect_show_vars)
 			return show_bisect_vars(&info, reaches, all);
 	}
 
 	traverse_commit_list(&revs, show_commit, show_object, &info);
 
+	stop_progress(&progress);
+
 	if (revs.count) {
 		if (revs.left_right && revs.cherry_mark)
 			printf("%d\t%d\t%d\n", revs.count_left, revs.count_right, revs.count_same);
 		else if (revs.left_right)
 			printf("%d\t%d\n", revs.count_left, revs.count_right);
 		else if (revs.cherry_mark)
