packet_buf_write(&req_buf,
						 "%s %s %s%c%s%s%s%s%s",
						 old_hex, new_hex, ref->name, 0,
						 status_report ? " report-status" : "",
						 use_sideband ? " side-band-64k" : "",
						 quiet ? " quiet" : "",
						 agent_supported ? " agent=" : "",
						 agent_supported ? git_user_agent_sanitized() : ""
						);