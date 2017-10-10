 		option_origin = "origin";
 
 	repo_name = argv[0];
 
 	path = get_repo_path(repo_name, &is_bundle);
 	if (path)
-		repo = xstrdup(absolute_path(repo_name));
+		repo = absolute_pathdup(repo_name);
 	else if (!strchr(repo_name, ':'))
 		die(_("repository '%s' does not exist"), repo_name);
 	else
 		repo = repo_name;
 
 	/* no need to be strict, transport_set_option() will validate it again */
