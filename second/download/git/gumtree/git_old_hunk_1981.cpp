
	si->shallow_ref[cmd->index] = 0;
	sha1_array_clear(&extra);
	return 0;
}

static const char *update(struct command *cmd, struct shallow_info *si)
{
	const char *name = cmd->ref_name;
	struct strbuf namespaced_name_buf = STRBUF_INIT;
	const char *namespaced_name;
	unsigned char *old_sha1 = cmd->old_sha1;
	unsigned char *new_sha1 = cmd->new_sha1;

	/* only refs/... are allowed */
	if (!starts_with(name, "refs/") || check_refname_format(name + 5, 0)) {
		rp_error("refusing to create funny ref '%s' remotely", name);
