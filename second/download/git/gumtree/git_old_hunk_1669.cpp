		die(_("A branch named '%s' already exists."), ref->buf + strlen("refs/heads/"));

	if (!attr_only) {
		const char *head;
		unsigned char sha1[20];

		head = resolve_ref_unsafe("HEAD", sha1, 0, NULL);
		if (!is_bare_repository() && head && !strcmp(head, ref->buf))
			die(_("Cannot force update the current branch."));
	}
	return 1;
}

