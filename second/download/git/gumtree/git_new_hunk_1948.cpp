			 * of the buffer.
			 */
			char *bp;

			bp = find_beginning_of_line(buf, scanp);

			if (*bp == '\n') {
				/*
				 * The newline is the end of the previous line,
				 * so we know we have complete line starting
				 * at (bp + 1). Prefix it onto any prior data
				 * we collected for the line and process it.
				 */
				strbuf_splice(&sb, 0, 0, bp + 1, endp - (bp + 1));
				scanp = bp;
				endp = bp + 1;
				ret = show_one_reflog_ent(&sb, fn, cb_data);
				strbuf_reset(&sb);
				if (ret)
					break;
			} else if (!pos) {
				/*
				 * We are at the start of the buffer, and the
				 * start of the file; there is no previous
				 * line, and we have everything for this one.
				 * Process it, and we can end the loop.
				 */
				strbuf_splice(&sb, 0, 0, buf, endp - buf);
				ret = show_one_reflog_ent(&sb, fn, cb_data);
				strbuf_reset(&sb);
				break;
			}

			if (bp == buf) {
				/*
				 * We are at the start of the buffer, and there
				 * is more file to read backwards. Which means
				 * we are in the middle of a line. Note that we
				 * may get here even if *bp was a newline; that
				 * just means we are at the exact end of the
				 * previous line, rather than some spot in the
				 * middle.
				 *
				 * Save away what we have to be combined with
				 * the data from the next read.
				 */
				strbuf_splice(&sb, 0, 0, buf, endp - buf);
				break;
			}
		}

	}
	if (!ret && sb.len)
		die("BUG: reverse reflog parser had leftover data");

	fclose(logfp);
	strbuf_release(&sb);
	return ret;
}

