			 * of the buffer.
			 */
			char *bp;

			bp = find_beginning_of_line(buf, scanp);

			if (*bp != '\n') {
				strbuf_splice(&sb, 0, 0, buf, endp - buf);
				if (pos)
					break; /* need to fill another block */
				scanp = buf - 1; /* leave loop */
			} else {
				/*
				 * (bp + 1) thru endp is the beginning of the
				 * current line we have in sb
				 */
				strbuf_splice(&sb, 0, 0, bp + 1, endp - (bp + 1));
				scanp = bp;
				endp = bp + 1;
			}
			ret = show_one_reflog_ent(&sb, fn, cb_data);
			strbuf_reset(&sb);
			if (ret)
				break;
		}

	}
	if (!ret && sb.len)
		ret = show_one_reflog_ent(&sb, fn, cb_data);

	fclose(logfp);
	strbuf_release(&sb);
	return ret;
}

