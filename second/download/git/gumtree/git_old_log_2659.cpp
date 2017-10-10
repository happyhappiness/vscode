packet_buf_write(&preamble, "%s %s\n",
				 sha1_to_hex(ref->old_sha1), ref->name);