			else if (opts->merge)
				errs |= checkout_merged(pos, &state);
			pos = skip_same_name(ce, pos) - 1;
		}
	}

	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	read_ref_full("HEAD", rev, 0, &flag);
	head = lookup_commit_reference_gently(rev, 1);

	errs |= post_checkout_hook(head, head, 0);
