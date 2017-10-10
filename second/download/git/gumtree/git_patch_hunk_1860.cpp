 }
 
 static size_t parse_color(struct strbuf *sb, /* in UTF-8 */
 			  const char *placeholder,
 			  struct format_commit_context *c)
 {
+	const char *rest = placeholder;
+
 	if (placeholder[1] == '(') {
 		const char *begin = placeholder + 2;
 		const char *end = strchr(begin, ')');
 		char color[COLOR_MAXLEN];
 
 		if (!end)
 			return 0;
-		if (starts_with(begin, "auto,")) {
+		if (skip_prefix(begin, "auto,", &begin)) {
 			if (!want_color(c->pretty_ctx->color))
 				return end - placeholder + 1;
-			begin += 5;
 		}
-		color_parse_mem(begin,
-				end - begin,
-				"--pretty format", color);
+		if (color_parse_mem(begin, end - begin, color) < 0)
+			die(_("unable to parse --pretty format"));
 		strbuf_addstr(sb, color);
 		return end - placeholder + 1;
 	}
-	if (starts_with(placeholder + 1, "red")) {
+	if (skip_prefix(placeholder + 1, "red", &rest))
 		strbuf_addstr(sb, GIT_COLOR_RED);
-		return 4;
-	} else if (starts_with(placeholder + 1, "green")) {
+	else if (skip_prefix(placeholder + 1, "green", &rest))
 		strbuf_addstr(sb, GIT_COLOR_GREEN);
-		return 6;
-	} else if (starts_with(placeholder + 1, "blue")) {
+	else if (skip_prefix(placeholder + 1, "blue", &rest))
 		strbuf_addstr(sb, GIT_COLOR_BLUE);
-		return 5;
-	} else if (starts_with(placeholder + 1, "reset")) {
+	else if (skip_prefix(placeholder + 1, "reset", &rest))
 		strbuf_addstr(sb, GIT_COLOR_RESET);
-		return 6;
-	} else
-		return 0;
+	return rest - placeholder;
 }
 
 static size_t parse_padding_placeholder(struct strbuf *sb,
 					const char *placeholder,
 					struct format_commit_context *c)
 {
