			    : !!(compat_flags & CF_SYMLINK_TIMES);
		}
#if defined HAVE_LUTIMES && defined HAVE_UTIMES
		else
			receiver_symlink_times = 1;
#endif
		if (inc_recurse && !allow_inc_recurse) {
			/* This should only be able to happen in a batch. */
			fprintf(stderr,
			    "Incompatible options specified for inc-recursive %s.\n",
			    read_batch ? "batch file" : "connection");
			exit_cleanup(RERR_SYNTAX);
