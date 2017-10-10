fprintf(stderr, "You can amend the commit now, with\n"
			"\n"
			"  git commit --amend %s\n"
			"\n"
			"Once you are satisfied with your changes, run\n"
			"\n"
			"  git rebase --continue\n", gpg_sign_opt_quoted(opts));