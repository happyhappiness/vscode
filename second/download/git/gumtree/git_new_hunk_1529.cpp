			error("cannot fdopen %s (%s)",
			      get_lock_file_path(&reflog_lock), strerror(errno));
			goto failure;
		}
	}

	hashcpy(oid.hash, sha1);

	(*prepare_fn)(refname, &oid, cb.policy_cb);
	refs_for_each_reflog_ent(ref_store, refname, expire_reflog_ent, &cb);
	(*cleanup_fn)(cb.policy_cb);

	if (!(flags & EXPIRE_REFLOGS_DRY_RUN)) {
		/*
		 * It doesn't make sense to adjust a reference pointed
