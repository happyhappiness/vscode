		 * might be better to always use chroot.
		 *
		 * So, perhaps if we can't chroot we should just issue
		 * a warning, unless a "require chroot" flag is set,
		 * in which case we fail.
		 */
		if (chroot(lp_path(i))) {
			rsyserr(FLOG, errno, "chroot %s failed",
				lp_path(i));
			io_printf(f_out, "@ERROR: chroot failed\n");
			return -1;
		}

		if (!push_dir("/", 0)) {
			rsyserr(FLOG, errno, "chdir %s failed\n",
				lp_path(i));
			io_printf(f_out, "@ERROR: chdir failed\n");
			return -1;
		}

	} else {
		if (!push_dir(lp_path(i), 0)) {
			rsyserr(FLOG, errno, "chdir %s failed\n",
				lp_path(i));
			io_printf(f_out, "@ERROR: chdir failed\n");
			return -1;
		}
		sanitize_paths = 1;
	}

	if (am_root) {
		/* XXXX: You could argue that if the daemon is started
		 * by a non-root user and they explicitly specify a
		 * gid, then we should try to change to that gid --
		 * this could be possible if it's already in their
		 * supplementary groups. */
