rp_error("refusing inconsistent update between symref '%s' (%s..%s) and"
		 " its target '%s' (%s..%s)",
		 cmd->ref_name,
		 find_unique_abbrev(cmd->old_sha1, DEFAULT_ABBREV),
		 find_unique_abbrev(cmd->new_sha1, DEFAULT_ABBREV),
		 dst_cmd->ref_name,
		 find_unique_abbrev(dst_cmd->old_sha1, DEFAULT_ABBREV),
		 find_unique_abbrev(dst_cmd->new_sha1, DEFAULT_ABBREV));