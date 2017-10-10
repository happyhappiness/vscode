	}

	filter_refs(args, refs, sought, nr_sought);

	for (retval = 1, ref = *refs; ref ; ref = ref->next) {
		const unsigned char *remote = ref->old_sha1;
		unsigned char local[20];
		struct object *o;

		o = lookup_object(remote);
		if (!o || !(o->flags & COMPLETE)) {
			retval = 0;
			if (!args->verbose)
				continue;
			fprintf(stderr,
				"want %s (%s)\n", sha1_to_hex(remote),
				ref->name);
			continue;
		}

		hashcpy(ref->new_sha1, local);
		if (!args->verbose)
			continue;
		fprintf(stderr,
			"already have %s (%s)\n", sha1_to_hex(remote),
			ref->name);
	}
