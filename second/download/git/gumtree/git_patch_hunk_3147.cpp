 	} else {
 		if (cached)
 			die(_("both --cached and trees are given."));
 		hit = grep_objects(&opt, &pathspec, &list);
 	}
 
-	if (use_threads)
+	if (num_threads)
 		hit |= wait_all();
 	if (hit && show_in_pager)
 		run_pager(&opt, prefix);
 	free_grep_patterns(&opt);
 	return !hit;
 }
