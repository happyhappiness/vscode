 
 	if (stat(file, &st))
 		die_errno(_("Could not stat '%s'"), file);
 	if (!st.st_size)
 		die(_("Empty patch. Aborted."));
 
-	memset(&child, 0, sizeof(child));
 	child.git_cmd = 1;
 	child.argv = apply_argv;
 	if (run_command(&child))
 		die(_("Could not apply '%s'"), file);
 
 	unlink(file);
