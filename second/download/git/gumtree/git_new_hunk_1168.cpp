		if (!allow_revs) {
			if (seen_dashdash)
				die(_("--no-index or --untracked cannot be used with revs"));
			break;
		}

		if (get_sha1_with_context(arg, GET_SHA1_RECORD_PATH,
					  oid.hash, &oc)) {
			if (seen_dashdash)
				die(_("unable to resolve revision: %s"), arg);
			break;
		}

		object = parse_object_or_die(oid.hash, arg);
		if (!seen_dashdash)
			verify_non_filename(prefix, arg);
		add_object_array_with_path(object, arg, &list, oc.mode, oc.path);
		free(oc.path);
	}

	/*
	 * Anything left over is presumed to be a path. But in the non-dashdash
	 * "do what I mean" case, we verify and complain when that isn't true.
	 */
