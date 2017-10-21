		sanitize_paths = 1;

	if ((munge_symlinks = lp_munge_symlinks(i)) < 0)
		munge_symlinks = !use_chroot || module_dirlen;
	if (munge_symlinks) {
		STRUCT_STAT st;
		char prefix[SYMLINK_PREFIX_LEN]; /* NOT +1 ! */
		strlcpy(prefix, SYMLINK_PREFIX, sizeof prefix); /* trim the trailing slash */
		if (do_stat(prefix, &st) == 0 && S_ISDIR(st.st_mode)) {
			rprintf(FLOG, "Symlink munging is unsafe when a %s directory exists.\n",
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
		/* pw is set if the user wants all the user's groups. */
		if (pw && initgroups(pw->pw_name, pw->pw_gid) < 0) {
			rsyserr(FLOG, errno, "initgroups failed");
			io_printf(f_out, "@ERROR: initgroups failed\n");
			return -1;
		}
#endif
	}

	if (set_uid) {
		if (setuid(uid) < 0
#ifdef HAVE_SETEUID
		 || seteuid(uid) < 0
#endif
		) {
			rsyserr(FLOG, errno, "setuid %ld failed", (long)uid);
			io_printf(f_out, "@ERROR: setuid failed\n");
			return -1;
		}

		am_root = (MY_UID() == 0);
	}
