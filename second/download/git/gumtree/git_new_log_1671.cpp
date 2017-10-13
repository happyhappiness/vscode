packet_buf_write(&req_buf,
					 "%s %s %s%c%s",
					 old_hex, new_hex, ref->name, 0,
					 cap_buf.buf);