		 * it is normal for the empty directory 'foo'
		 * to remain.
		 */
		ref_file = git_path("%s", orig_refname);
		if (remove_empty_directories(ref_file)) {
			last_errno = errno;

			if (!verify_refname_available(orig_refname, extras, skip,
						      get_loose_refs(&ref_cache), err))
				strbuf_addf(err, "there are still refs under '%s'",
					    orig_refname);

			goto error_return;
		}
		refname = resolve_ref_unsafe(orig_refname, resolve_flags,
					     lock->old_sha1, &type);
	}
	if (type_p)
	    *type_p = type;
	if (!refname) {
		last_errno = errno;
		if (last_errno != ENOTDIR ||
		    !verify_refname_available(orig_refname, extras, skip,
					      get_loose_refs(&ref_cache), err))
			strbuf_addf(err, "unable to resolve reference %s: %s",
				    orig_refname, strerror(last_errno));

		goto error_return;
	}
	/*
	 * If the ref did not exist and we are creating it, make sure
	 * there is no existing packed ref whose name begins with our
	 * refname, nor a packed ref whose name is a proper prefix of
	 * our refname.
	 */
	if (is_null_sha1(lock->old_sha1) &&
	    verify_refname_available(refname, extras, skip,
				     get_packed_refs(&ref_cache), err)) {
		last_errno = ENOTDIR;
		goto error_return;
	}

	lock->lk = xcalloc(1, sizeof(struct lock_file));

