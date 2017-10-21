				prefix);
			io_printf(f_out, "@ERROR: daemon security issue -- contact admin\n", name);
			exit_cleanup(RERR_UNSUPPORTED);
		}
	}

	if (gid_count) {
		if (setgid(gid_list[0])) {
			rsyserr(FLOG, errno, "setgid %ld failed", (long)gid_list[0]);
			io_printf(f_out, "@ERROR: setgid failed\n");
			return -1;
		}
#ifdef HAVE_SETGROUPS
		/* Set the group(s) we want to be active. */
		if (setgroups(gid_count, gid_list)) {
			rsyserr(FLOG, errno, "setgroups failed");
			io_printf(f_out, "@ERROR: setgroups failed\n");
			return -1;
		}
#endif
#if defined HAVE_INITGROUPS && !defined HAVE_GETGROUPLIST
