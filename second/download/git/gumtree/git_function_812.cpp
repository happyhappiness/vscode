static int create_graft(int argc, const char **argv, int force)
{
	unsigned char old[20], new[20];
	const char *old_ref = argv[0];
	struct commit *commit;
	struct strbuf buf = STRBUF_INIT;
	const char *buffer;
	unsigned long size;

	if (get_sha1(old_ref, old) < 0)
		die(_("Not a valid object name: '%s'"), old_ref);
	commit = lookup_commit_or_die(old, old_ref);

	buffer = get_commit_buffer(commit, &size);
	strbuf_add(&buf, buffer, size);
	unuse_commit_buffer(commit, buffer);

	replace_parents(&buf, argc - 1, &argv[1]);

	if (remove_signature(&buf)) {
		warning(_("the original commit '%s' has a gpg signature."), old_ref);
		warning(_("the signature will be removed in the replacement commit!"));
	}

	check_mergetags(commit, argc, argv);

	if (write_sha1_file(buf.buf, buf.len, commit_type, new))
		die(_("could not write replacement commit for: '%s'"), old_ref);

	strbuf_release(&buf);

	if (!hashcmp(old, new))
		return error("new commit is the same as the old one: '%s'", sha1_to_hex(old));

	return replace_object_sha1(old_ref, old, "replacement", new, force);
}