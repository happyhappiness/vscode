packet_write(1, "%s %s%c%s%s agent=%s\n",
			     sha1_to_hex(sha1), path, 0,
			     " report-status delete-refs side-band-64k quiet",
			     prefer_ofs_delta ? " ofs-delta" : "",
			     git_user_agent_sanitized());