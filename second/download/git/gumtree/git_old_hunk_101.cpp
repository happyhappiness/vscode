		if (!ep)
			return error("malformed format string %s", sp);
		/* sp points at "%(" and ep points at the closing ")" */
		at = parse_atom(sp + 2, ep);
		cp = ep + 1;

		if (!memcmp(used_atom[at], "color:", 6))
			need_color_reset_at_eol = !!strcmp(used_atom[at], color_reset);
	}
	return 0;
}

/*
