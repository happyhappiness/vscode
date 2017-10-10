 	 */
 	s->hints = 0;
 
 	if (clean_message_contents)
 		stripspace(&sb, 0);
 
-	if (signoff) {
-		/*
-		 * See if we have a Conflicts: block at the end. If yes, count
-		 * its size, so we can ignore it.
-		 */
-		int ignore_footer = 0;
-		int i, eol, previous = 0;
-		const char *nl;
-
-		for (i = 0; i < sb.len; i++) {
-			nl = memchr(sb.buf + i, '\n', sb.len - i);
-			if (nl)
-				eol = nl - sb.buf;
-			else
-				eol = sb.len;
-			if (starts_with(sb.buf + previous, "\nConflicts:\n")) {
-				ignore_footer = sb.len - previous;
-				break;
-			}
-			while (i < eol)
-				i++;
-			previous = eol;
-		}
-
-		append_signoff(&sb, ignore_footer, 0);
-	}
+	if (signoff)
+		append_signoff(&sb, ignore_non_trailer(&sb), 0);
 
 	if (fwrite(sb.buf, 1, sb.len, s->fp) < sb.len)
 		die_errno(_("could not write commit template"));
 
 	if (auto_comment_line_char)
 		adjust_comment_line_char(&sb);
