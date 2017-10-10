 	if (0 <= option_verbosity)
 		fprintf(stderr, _("done.\n"));
 }
 
 static const char *junk_work_tree;
 static const char *junk_git_dir;
-static pid_t junk_pid;
 static enum {
 	JUNK_LEAVE_NONE,
 	JUNK_LEAVE_REPO,
 	JUNK_LEAVE_ALL
 } junk_mode = JUNK_LEAVE_NONE;
 
