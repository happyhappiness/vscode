		 * acquiring the lock.
		 */
		rollback_packed_refs();
		return 0;
	}

	/* Write what remains */
	ret = commit_packed_refs();
	if (ret)
		strbuf_addf(err, "unable to overwrite old ref-pack file: %s",
			    strerror(errno));
	return ret;
