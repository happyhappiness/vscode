		 * acquiring the lock.
		 */
		rollback_packed_refs();
		return 0;
	}

	/* Remove any other accumulated cruft */
	do_for_each_entry_in_dir(packed, 0, curate_packed_ref_fn, &refs_to_delete);
	for_each_string_list_item(ref_to_delete, &refs_to_delete) {
		if (remove_entry(packed, ref_to_delete->string) == -1)
			die("internal error");
	}

	/* Write what remains */
	ret = commit_packed_refs();
	if (ret)
		strbuf_addf(err, "unable to overwrite old ref-pack file: %s",
			    strerror(errno));
	return ret;
