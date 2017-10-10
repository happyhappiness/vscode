 	if (path)
 		repo = xstrdup(absolute_path(repo_name));
 	else if (!strchr(repo_name, ':'))
 		die(_("repository '%s' does not exist"), repo_name);
 	else
 		repo = repo_name;
-	is_local = option_local != 0 && path && !is_bundle;
-	if (is_local) {
-		if (option_depth)
-			warning(_("--depth is ignored in local clones; use file:// instead."));
-		if (!access(mkpath("%s/shallow", path), F_OK)) {
-			if (option_local > 0)
-				warning(_("source repository is shallow, ignoring --local"));
-			is_local = 0;
-		}
-	}
-	if (option_local > 0 && !is_local)
-		warning(_("--local is ignored"));
 
 	/* no need to be strict, transport_set_option() will validate it again */
 	if (option_depth && atoi(option_depth) < 1)
 		die(_("depth %s is not a positive number"), option_depth);
 
 	if (argc == 2)
