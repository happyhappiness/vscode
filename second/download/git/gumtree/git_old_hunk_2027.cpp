		case '@': case '\\':
			/* Ignore it, we already handled it */
			break;
		default:
			if (apply_verbosely)
				error(_("invalid start of line: '%c'"), first);
			return -1;
		}
		if (added_blank_line) {
			if (!new_blank_lines_at_end)
				found_new_blank_lines_at_end = hunk_linenr;
			new_blank_lines_at_end++;
		}
