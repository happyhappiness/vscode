{
		/*
		 * User didn't request full permissions, so don't
		 * restore SUID, SGID bits and obey umask.
		 */
		a->mode &= ~S_ISUID;
		a->mode &= ~S_ISGID;
		a->mode &= ~S_ISVTX;
		a->mode &= ~a->user_umask;
	}