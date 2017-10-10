 		return -1;
 
 	die_errno(_("could not read '%s'"), am_path(state, file));
 }
 
 /**
- * Reads a KEY=VALUE shell variable assignment from `fp`, returning the VALUE
- * as a newly-allocated string. VALUE must be a quoted string, and the KEY must
- * match `key`. Returns NULL on failure.
- *
- * This is used by read_author_script() to read the GIT_AUTHOR_* variables from
- * the author-script.
+ * Take a series of KEY='VALUE' lines where VALUE part is
+ * sq-quoted, and append <KEY, VALUE> at the end of the string list
  */
-static char *read_shell_var(FILE *fp, const char *key)
+static int parse_key_value_squoted(char *buf, struct string_list *list)
 {
-	struct strbuf sb = STRBUF_INIT;
-	const char *str;
-
-	if (strbuf_getline_lf(&sb, fp))
-		goto fail;
-
-	if (!skip_prefix(sb.buf, key, &str))
-		goto fail;
-
-	if (!skip_prefix(str, "=", &str))
-		goto fail;
-
-	strbuf_remove(&sb, 0, str - sb.buf);
-
-	str = sq_dequote(sb.buf);
-	if (!str)
-		goto fail;
-
-	return strbuf_detach(&sb, NULL);
-
-fail:
-	strbuf_release(&sb);
-	return NULL;
+	while (*buf) {
+		struct string_list_item *item;
+		char *np;
+		char *cp = strchr(buf, '=');
+		if (!cp)
+			return -1;
+		np = strchrnul(cp, '\n');
+		*cp++ = '\0';
+		item = string_list_append(list, buf);
+
+		buf = np + (*np == '\n');
+		*np = '\0';
+		cp = sq_dequote(cp);
+		if (!cp)
+			return -1;
+		item->util = xstrdup(cp);
+	}
+	return 0;
 }
 
 /**
  * Reads and parses the state directory's "author-script" file, and sets
  * state->author_name, state->author_email and state->author_date accordingly.
  * Returns 0 on success, -1 if the file could not be parsed.
