
		if (setgid(gid)) {
			rsyserr(FERROR, errno, "setgid %d failed", (int) gid);
			io_printf(f_out, "@ERROR: setgid failed\n");
			return -1;
		}
#ifdef HAVE_SETGROUPS
		/* Get rid of any supplementary groups this process
		 * might have inheristed. */
		if (setgroups(1, &gid)) {
			rsyserr(FERROR, errno, "setgroups failed");
			io_printf(f_out, "@ERROR: setgroups failed\n");
			return -1;
		}
#endif

		if (setuid(uid)) {
			rsyserr(FERROR, errno, "setuid %d failed", (int) uid);
			io_printf(f_out, "@ERROR: setuid failed\n");
			return -1;
		}
