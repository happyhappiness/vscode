 	struct checkout state;
 	static char *ps_matched;
 	unsigned char rev[20];
 	int flag;
 	struct commit *head;
 	int errs = 0;
-	int newfd;
 	struct lock_file *lock_file;
 
 	if (opts->track != BRANCH_TRACK_UNSPECIFIED)
 		die(_("'%s' cannot be used with updating paths"), "--track");
 
 	if (opts->new_branch_log)
