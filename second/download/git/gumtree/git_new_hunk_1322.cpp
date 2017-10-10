		error(_("too many parameters"));
		usage_with_options(git_notes_show_usage, options);
	}

	object_ref = argc ? argv[0] : "HEAD";

	if (get_oid(object_ref, &object))
		die(_("failed to resolve '%s' as a valid ref."), object_ref);

	t = init_notes_check("show", 0);
	note = get_note(t, &object);

	if (!note)
		retval = error(_("no note found for object %s."),
			       oid_to_hex(&object));
	else {
		const char *show_args[3] = {"show", oid_to_hex(note), NULL};
		retval = execv_git_cmd(show_args);
	}
	free_notes(t);
	return retval;
}

