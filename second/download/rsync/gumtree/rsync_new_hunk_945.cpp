			/* This should only be able to happen in a batch. */
			fprintf(stderr,
			    "Incompatible options specified for inc-recursive %s.\n",
			    read_batch ? "batch file" : "connection");
			exit_cleanup(RERR_SYNTAX);
		}
		use_safe_inc_flist = !!(compat_flags & CF_SAFE_FLIST);
		need_messages_from_generator = 1;
#if defined HAVE_LUTIMES && defined HAVE_UTIMES
	} else if (!am_sender) {
		receiver_symlink_times = 1;
#endif
	}
