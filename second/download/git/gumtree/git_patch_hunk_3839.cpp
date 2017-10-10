 	one = quote_path(one_name, s->prefix, &onebuf);
 	two = quote_path(two_name, s->prefix, &twobuf);
 
 	status_printf(s, color(WT_STATUS_HEADER, s), "\t");
 	what = wt_status_diff_status_string(status);
 	if (!what)
-		die(_("bug: unhandled diff status %c"), status);
+		die("BUG: unhandled diff status %c", status);
 	len = label_width - utf8_strwidth(what);
 	assert(len >= 0);
 	if (status == DIFF_STATUS_COPIED || status == DIFF_STATUS_RENAMED)
 		status_printf_more(s, c, "%s%.*s%s -> %s",
 				   what, len, padding, one, two);
 	else
