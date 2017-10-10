		if (cb->flags & EXPIRE_REFLOGS_VERBOSE)
			printf("keep %s", message);
	}
	return 0;
}

int reflog_expire(const char *refname, const unsigned char *sha1,
		 unsigned int flags,
		 reflog_expiry_prepare_fn prepare_fn,
		 reflog_expiry_should_prune_fn should_prune_fn,
		 reflog_expiry_cleanup_fn cleanup_fn,
		 void *policy_cb_data)
{
	static struct lock_file reflog_lock;
	struct expire_reflog_cb cb;
	struct ref_lock *lock;
	char *log_file;
	int status = 0;
	int type;
