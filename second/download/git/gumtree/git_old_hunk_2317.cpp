		int head_flag;
		const char *head_ref;
		head_ref = resolve_ref_unsafe("HEAD", RESOLVE_REF_READING,
					      head_sha1, &head_flag);
		if (head_ref && (head_flag & REF_ISSYMREF) &&
		    !strcmp(head_ref, lock->ref_name))
			log_ref_write("HEAD", lock->old_sha1, sha1, logmsg);
	}
	if (commit_ref(lock)) {
		error("Couldn't set %s", lock->ref_name);
		unlock_ref(lock);
		return -1;
	}
