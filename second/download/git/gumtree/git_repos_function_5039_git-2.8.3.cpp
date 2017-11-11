static void check_aliased_update(struct command *cmd, struct string_list *list)
{
	struct strbuf buf = STRBUF_INIT;
	const char *dst_name;
	struct string_list_item *item;
	struct command *dst_cmd;
	unsigned char sha1[GIT_SHA1_RAWSZ];
	char cmd_oldh[GIT_SHA1_HEXSZ + 1],
	     cmd_newh[GIT_SHA1_HEXSZ + 1],
	     dst_oldh[GIT_SHA1_HEXSZ + 1],
	     dst_newh[GIT_SHA1_HEXSZ + 1];
	int flag;

	strbuf_addf(&buf, "%s%s", get_git_namespace(), cmd->ref_name);
	dst_name = resolve_ref_unsafe(buf.buf, 0, sha1, &flag);
	strbuf_release(&buf);

	if (!(flag & REF_ISSYMREF))
		return;

	dst_name = strip_namespace(dst_name);
	if (!dst_name) {
		rp_error("refusing update to broken symref '%s'", cmd->ref_name);
		cmd->skip_update = 1;
		cmd->error_string = "broken symref";
		return;
	}

	if ((item = string_list_lookup(list, dst_name)) == NULL)
		return;

	cmd->skip_update = 1;

	dst_cmd = (struct command *) item->util;

	if (!hashcmp(cmd->old_sha1, dst_cmd->old_sha1) &&
	    !hashcmp(cmd->new_sha1, dst_cmd->new_sha1))
		return;

	dst_cmd->skip_update = 1;

	find_unique_abbrev_r(cmd_oldh, cmd->old_sha1, DEFAULT_ABBREV);
	find_unique_abbrev_r(cmd_newh, cmd->new_sha1, DEFAULT_ABBREV);
	find_unique_abbrev_r(dst_oldh, dst_cmd->old_sha1, DEFAULT_ABBREV);
	find_unique_abbrev_r(dst_newh, dst_cmd->new_sha1, DEFAULT_ABBREV);
	rp_error("refusing inconsistent update between symref '%s' (%s..%s) and"
		 " its target '%s' (%s..%s)",
		 cmd->ref_name, cmd_oldh, cmd_newh,
		 dst_cmd->ref_name, dst_oldh, dst_newh);

	cmd->error_string = dst_cmd->error_string =
		"inconsistent aliased update";
}