		prepare_show_merge(revs);
	if (revs->def && !revs->pending.nr && !got_rev_arg) {
		unsigned char sha1[20];
		struct object *object;
		struct object_context oc;
		if (get_sha1_with_context(revs->def, 0, sha1, &oc))
			diagnose_missing_default(revs->def);
		object = get_reference(revs, revs->def, sha1, 0);
		add_pending_object_with_mode(revs, object, revs->def, oc.mode);
	}

	/* Did the user ask for any diff output? Run the diff! */
	if (revs->diffopt.output_format & ~DIFF_FORMAT_NO_OUTPUT)
