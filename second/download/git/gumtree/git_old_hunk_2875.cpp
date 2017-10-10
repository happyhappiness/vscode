	if (!hashcmp(cmd->old_sha1, dst_cmd->old_sha1) &&
	    !hashcmp(cmd->new_sha1, dst_cmd->new_sha1))
		return;

	dst_cmd->skip_update = 1;

	strcpy(cmd_oldh, find_unique_abbrev(cmd->old_sha1, DEFAULT_ABBREV));
	strcpy(cmd_newh, find_unique_abbrev(cmd->new_sha1, DEFAULT_ABBREV));
	strcpy(dst_oldh, find_unique_abbrev(dst_cmd->old_sha1, DEFAULT_ABBREV));
	strcpy(dst_newh, find_unique_abbrev(dst_cmd->new_sha1, DEFAULT_ABBREV));
	rp_error("refusing inconsistent update between symref '%s' (%s..%s) and"
		 " its target '%s' (%s..%s)",
		 cmd->ref_name, cmd_oldh, cmd_newh,
		 dst_cmd->ref_name, dst_oldh, dst_newh);

	cmd->error_string = dst_cmd->error_string =
