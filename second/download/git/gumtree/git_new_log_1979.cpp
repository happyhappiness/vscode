packet_write(1, "%s %s%c%s%s%s%s%s agent=%s\n",
			     oid_to_hex(oid), refname_nons,
			     0, capabilities,
			     (allow_unadvertised_object_request & ALLOW_TIP_SHA1) ?
				     " allow-tip-sha1-in-want" : "",
			     (allow_unadvertised_object_request & ALLOW_REACHABLE_SHA1) ?
				     " allow-reachable-sha1-in-want" : "",
			     stateless_rpc ? " no-done" : "",
			     symref_info.buf,
			     git_user_agent_sanitized());