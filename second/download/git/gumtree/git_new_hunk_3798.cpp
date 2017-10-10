					  logmsg, 0, &log_err)) {
				error("%s", log_err.buf);
				strbuf_release(&log_err);
			}
		}
	}

	if (commit_ref(lock)) {
		strbuf_addf(err, "couldn't set '%s'", lock->ref_name);
		unlock_ref(lock);
		return -1;
	}

	unlock_ref(lock);
	return 0;
