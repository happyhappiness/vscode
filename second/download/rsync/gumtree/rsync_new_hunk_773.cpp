		 *
		 * So, perhaps if we can't chroot we should just issue
		 * a warning, unless a "require chroot" flag is set,
		 * in which case we fail.
		 */
		if (chroot(lp_path(i))) {
			rsyserr(FLOG, errno, "chroot %s failed",
				safe_fname(lp_path(i)));
			io_printf(f_out, "@ERROR: chroot failed\n");
			return -1;
		}

		if (!push_dir("/")) {
			rsyserr(FLOG, errno, "chdir %s failed\n",
				safe_fname(lp_path(i)));
			io_printf(f_out, "@ERROR: chdir failed\n");
			return -1;
		}

	} else {
		if (!push_dir(lp_path(i))) {
			rsyserr(FLOG, errno, "chdir %s failed\n",
				safe_fname(lp_path(i)));
			io_printf(f_out, "@ERROR: chdir failed\n");
			return -1;
		}
		sanitize_paths = 1;
	}

