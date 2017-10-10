			switch (rm->fetch_head_status) {
			case FETCH_HEAD_NOT_FOR_MERGE:
				merge_status_marker = "not-for-merge";
				/* fall-through */
			case FETCH_HEAD_MERGE:
				fprintf(fp, "%s\t%s\t%s",
					oid_to_hex(&rm->old_oid),
					merge_status_marker,
					note.buf);
				for (i = 0; i < url_len; ++i)
					if ('\n' == url[i])
						fputs("\\n", fp);
					else
