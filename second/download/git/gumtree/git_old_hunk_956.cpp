		return;

	cmd->skip_update = 1;

	dst_cmd = (struct command *) item->util;

	if (!hashcmp(cmd->old_sha1, dst_cmd->old_sha1) &&
	    !hashcmp(cmd->new_sha1, dst_cmd->new_sha1))
		return;

	dst_cmd->skip_update = 1;

	rp_error("refusing inconsistent update between symref '%s' (%s..%s) and"
		 " its target '%s' (%s..%s)",
		 cmd->ref_name,
		 find_unique_abbrev(cmd->old_sha1, DEFAULT_ABBREV),
		 find_unique_abbrev(cmd->new_sha1, DEFAULT_ABBREV),
		 dst_cmd->ref_name,
		 find_unique_abbrev(dst_cmd->old_sha1, DEFAULT_ABBREV),
		 find_unique_abbrev(dst_cmd->new_sha1, DEFAULT_ABBREV));

	cmd->error_string = dst_cmd->error_string =
		"inconsistent aliased update";
}

static void check_aliased_updates(struct command *commands)
