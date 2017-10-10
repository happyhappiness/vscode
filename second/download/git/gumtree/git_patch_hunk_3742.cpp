 
 	if (!opt->header_list)
 		return NULL;
 
 	for (p = opt->header_list; p; p = p->next) {
 		if (p->token != GREP_PATTERN_HEAD)
-			die("bug: a non-header pattern in grep header list.");
+			die("BUG: a non-header pattern in grep header list.");
 		if (p->field < GREP_HEADER_FIELD_MIN ||
 		    GREP_HEADER_FIELD_MAX <= p->field)
-			die("bug: unknown header field %d", p->field);
+			die("BUG: unknown header field %d", p->field);
 		compile_regexp(p, opt);
 	}
 
 	for (fld = 0; fld < GREP_HEADER_FIELD_MAX; fld++)
 		header_group[fld] = NULL;
 
 	for (p = opt->header_list; p; p = p->next) {
 		struct grep_expr *h;
 		struct grep_pat *pp = p;
 
 		h = compile_pattern_atom(&pp);
 		if (!h || pp != p->next)
-			die("bug: malformed header expr");
+			die("BUG: malformed header expr");
 		if (!header_group[p->field]) {
 			header_group[p->field] = h;
 			continue;
 		}
 		header_group[p->field] = grep_or_expr(h, header_group[p->field]);
 	}
