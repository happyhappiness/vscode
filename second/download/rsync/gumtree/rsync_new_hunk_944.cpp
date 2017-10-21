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
