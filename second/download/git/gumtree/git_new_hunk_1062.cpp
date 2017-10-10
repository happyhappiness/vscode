		} else {
			error("unable to delete existing %s", newrefname);
			goto rollback;
		}
	}

	if (log && rename_tmp_log(refs, newrefname))
		goto rollback;

	logmoved = log;

	lock = lock_ref_sha1_basic(refs, newrefname, NULL, NULL, NULL,
				   REF_NODEREF, NULL, &err);
