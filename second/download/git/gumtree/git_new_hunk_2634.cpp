		unsigned char head_sha1[20];
		int head_flag;
		const char *head_ref;
		head_ref = resolve_ref_unsafe("HEAD", RESOLVE_REF_READING,
					      head_sha1, &head_flag);
		if (head_ref && (head_flag & REF_ISSYMREF) &&
		    !strcmp(head_ref, lock->ref_name)) {
			struct strbuf log_err = STRBUF_INIT;
			if (log_ref_write("HEAD", lock->old_oid.hash, sha1,
					  logmsg, 0, &log_err)) {
				error("%s", log_err.buf);
				strbuf_release(&log_err);
			}
		}
	}
	if (commit_ref(lock)) {
		error("Couldn't set %s", lock->ref_name);
		unlock_ref(lock);
		return -1;
	}
