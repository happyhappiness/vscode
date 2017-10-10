		 * of git. Note, we use octal numbers for new share modes,
		 * and compatibility values for PERM_GROUP and
		 * PERM_EVERYBODY.
		 */
		if (shared_repository < 0)
			/* force to the mode value */
			sprintf(buf, "0%o", -shared_repository);
		else if (shared_repository == PERM_GROUP)
			sprintf(buf, "%d", OLD_PERM_GROUP);
		else if (shared_repository == PERM_EVERYBODY)
			sprintf(buf, "%d", OLD_PERM_EVERYBODY);
		else
			die("oops");
		git_config_set("core.sharedrepository", buf);
		git_config_set("receive.denyNonFastforwards", "true");
	}

	if (!(flags & INIT_DB_QUIET)) {
		int len = strlen(git_dir);
