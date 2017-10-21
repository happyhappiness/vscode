			rsyserr(FLOG, errno, "chroot %s failed",
				lp_path(i));
			io_printf(f_out, "@ERROR: chroot failed\n");
			return -1;
		}

		if (!push_dir("/")) {
			rsyserr(FLOG, errno, "chdir %s failed\n",
				lp_path(i));
			io_printf(f_out, "@ERROR: chdir failed\n");
			return -1;
		}

	} else {
		if (!push_dir(lp_path(i))) {
			rsyserr(FLOG, errno, "chdir %s failed\n",
				lp_path(i));
			io_printf(f_out, "@ERROR: chdir failed\n");
			return -1;
		}
		sanitize_paths = 1;
