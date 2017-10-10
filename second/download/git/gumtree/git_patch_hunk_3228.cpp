 	need_color_reset_at_eol = 0;
 	for (cp = format; *cp && (sp = find_next(cp)); ) {
 		const char *color, *ep = strchr(sp, ')');
 		int at;
 
 		if (!ep)
-			return error("malformed format string %s", sp);
+			return error(_("malformed format string %s"), sp);
 		/* sp points at "%(" and ep points at the closing ")" */
 		at = parse_ref_filter_atom(sp + 2, ep);
 		cp = ep + 1;
 
-		if (skip_prefix(used_atom[at], "color:", &color))
+		if (skip_prefix(used_atom[at].name, "color:", &color))
 			need_color_reset_at_eol = !!strcmp(color, "reset");
 	}
 	return 0;
 }
 
 /*
