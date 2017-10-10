	strbuf_init(&name, PATH_MAX);
	retval = do_for_each_reflog(&name, fn, cb_data);
	strbuf_release(&name);
	return retval;
}

/**
 * Information needed for a single ref update.  Set new_sha1 to the
 * new value or to zero to delete the ref.  To check the old value
 * while locking the ref, set have_old to 1 and set old_sha1 to the
 * value or to zero to ensure the ref does not exist before update.
 */
