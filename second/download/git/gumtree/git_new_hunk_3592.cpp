			old += plen;
			if (first == '-')
				break;
		/* Fall-through for ' ' */
		case '+':
			/* --no-add does not add new lines */
			if (first == '+' && state->no_add)
				break;

			start = newlines.len;
			if (first != '+' ||
			    !state->whitespace_error ||
			    state->ws_error_action != correct_ws_error) {
				strbuf_add(&newlines, patch + 1, plen);
			}
			else {
				ws_fix_copy(&newlines, patch + 1, plen, ws_rule, &state->applied_after_fixing_ws);
			}
			add_line_info(&postimage, newlines.buf + start, newlines.len - start,
				      (first == '+' ? 0 : LINE_COMMON));
			if (first == '+' &&
			    (ws_rule & WS_BLANK_AT_EOF) &&
			    ws_blank_line(patch + 1, plen, ws_rule))
				added_blank_line = 1;
			break;
		case '@': case '\\':
			/* Ignore it, we already handled it */
			break;
		default:
			if (state->apply_verbosely)
				error(_("invalid start of line: '%c'"), first);
			applied_pos = -1;
			goto out;
		}
		if (added_blank_line) {
			if (!new_blank_lines_at_end)
