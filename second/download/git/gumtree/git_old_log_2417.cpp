fprintf(fp, "%s\t%s\t%s",
					sha1_to_hex(rm->old_sha1),
					merge_status_marker,
					note.buf);