		sanitize_paths = 1;

	if ((munge_symlinks = lp_munge_symlinks(i)) < 0)
		munge_symlinks = !use_chroot || module_dirlen;
	if (munge_symlinks) {
		STRUCT_STAT st;
		if (do_stat(SYMLINK_PREFIX, &st) == 0 && S_ISDIR(st.st_mode)) {
			rprintf(FLOG, "Symlink munging is unsupported when a %s directory exists.\n",
				SYMLINK_PREFIX);
			io_printf(f_out, "@ERROR: daemon security issue -- contact admin\n", name);
			exit_cleanup(RERR_UNSUPPORTED);
		}
	}

	if (am_root) {
		/* XXXX: You could argue that if the daemon is started
		 * by a non-root user and they explicitly specify a
		 * gid, then we should try to change to that gid --
		 * this could be possible if it's already in their
		 * supplementary groups. */

		/* TODO: Perhaps we need to document that if rsyncd is
		 * started by somebody other than root it will inherit
		 * all their supplementary groups. */

		if (setgid(gid)) {
			rsyserr(FLOG, errno, "setgid %d failed", (int)gid);
			io_printf(f_out, "@ERROR: setgid failed\n");
			return -1;
		}
#ifdef HAVE_SETGROUPS
		/* Get rid of any supplementary groups this process
		 * might have inheristed. */
		if (setgroups(1, &gid)) {
			rsyserr(FLOG, errno, "setgroups failed");
			io_printf(f_out, "@ERROR: setgroups failed\n");
			return -1;
		}
#endif

		if (setuid(uid) < 0
#ifdef HAVE_SETEUID
		 || seteuid(uid) < 0
#endif
		) {
			rsyserr(FLOG, errno, "setuid %d failed", (int)uid);
			io_printf(f_out, "@ERROR: setuid failed\n");
			return -1;
		}

		am_root = (MY_UID() == 0);
	}
