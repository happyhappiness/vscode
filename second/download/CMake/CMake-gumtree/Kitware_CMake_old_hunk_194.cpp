	if (a->restore_pwd >= 0) {

		r = fchdir(a->restore_pwd);

		if (r != 0) {

			archive_set_error(&a->archive, errno, "chdir() failure");

			ret = ARCHIVE_FATAL;

		}

		close(a->restore_pwd);

