 		 */
 		strbuf_setlen(var, baselen);
 		strbuf_addch(var, tolower(c));
 		if (get_value(fn, data, var) < 0)
 			break;
 	}
+
+	switch (cf->origin_type) {
+	case CONFIG_ORIGIN_BLOB:
+		error_msg = xstrfmt(_("bad config line %d in blob %s"),
+				      cf->linenr, cf->name);
+		break;
+	case CONFIG_ORIGIN_FILE:
+		error_msg = xstrfmt(_("bad config line %d in file %s"),
+				      cf->linenr, cf->name);
+		break;
+	case CONFIG_ORIGIN_STDIN:
+		error_msg = xstrfmt(_("bad config line %d in standard input"),
+				      cf->linenr);
+		break;
+	case CONFIG_ORIGIN_SUBMODULE_BLOB:
+		error_msg = xstrfmt(_("bad config line %d in submodule-blob %s"),
+				       cf->linenr, cf->name);
+		break;
+	case CONFIG_ORIGIN_CMDLINE:
+		error_msg = xstrfmt(_("bad config line %d in command line %s"),
+				       cf->linenr, cf->name);
+		break;
+	default:
+		error_msg = xstrfmt(_("bad config line %d in %s"),
+				      cf->linenr, cf->name);
+	}
+
 	if (cf->die_on_error)
-		die(_("bad config line %d in %s %s"), cf->linenr, cf->origin_type, cf->name);
+		die("%s", error_msg);
 	else
-		return error(_("bad config line %d in %s %s"), cf->linenr, cf->origin_type, cf->name);
+		error_return = error("%s", error_msg);
+
+	free(error_msg);
+	return error_return;
 }
 
 static int parse_unit_factor(const char *end, uintmax_t *val)
 {
 	if (!*end)
 		return 1;
