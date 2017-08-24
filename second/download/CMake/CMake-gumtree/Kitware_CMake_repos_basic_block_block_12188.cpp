{
			int last_is_path, keywords;

			keywords = bid_entry(p, len, nl, &last_is_path);
			if (keywords >= 0) {
				detected_bytes += len;
				if (form_D == 0) {
					if (last_is_path)
						form_D = 1;
					else if (keywords > 0)
						/* This line is not `form D'. */
						form_D = -1;
				} else if (form_D == 1) {
					if (!last_is_path && keywords > 0)
						/* This this is not `form D'
						 * and We cannot accept mixed
						 * format. */
						break;
				}
				if (!last_is_path && p[len-nl-1] == '\\')
					/* This line continues. */
					multiline = 1;
				else {
					/* We've got plenty of correct lines
					 * to assume that this file is a mtree
					 * format. */
					if (++entry_cnt >= MAX_BID_ENTRY)
						break;
				}
			} else
				break;
		}