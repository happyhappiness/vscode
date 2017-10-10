	existing = find_shared_symref("HEAD", branch);
	if (existing) {
		skip_prefix(branch, "refs/heads/", &branch);
		die(_("'%s' is already checked out at '%s'"), branch, existing);
	}
}
