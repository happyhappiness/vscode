static void read_idx_option(struct pack_idx_option *opts, const char *pack_name)
{
	struct packed_git *p = add_packed_git(pack_name, strlen(pack_name), 1);

	if (!p)
		die(_("Cannot open existing pack file '%s'"), pack_name);
	if (open_pack_index(p))
		die(_("Cannot open existing pack idx file for '%s'"), pack_name);

	/* Read the attributes from the existing idx file */
	opts->version = p->index_version;

	if (opts->version == 2)
		read_v2_anomalous_offsets(p, opts);

	/*
	 * Get rid of the idx file as we do not need it anymore.
	 * NEEDSWORK: extract this bit from free_pack_by_name() in
	 * sha1_file.c, perhaps?  It shouldn't matter very much as we
	 * know we haven't installed this pack (hence we never have
	 * read anything from it).
	 */
	close_pack_index(p);
	free(p);
}