 	N_("git update-ref [options] -d <refname> [<oldval>]"),
 	N_("git update-ref [options]    <refname> <newval> [<oldval>]"),
 	N_("git update-ref [options] --stdin [-z]"),
 	NULL
 };
 
-static int updates_alloc;
-static int updates_count;
-static const struct ref_update **updates;
+static struct ref_transaction *transaction;
 
 static char line_termination = '\n';
 static int update_flags;
+static struct strbuf err = STRBUF_INIT;
 
-static struct ref_update *update_alloc(void)
-{
-	struct ref_update *update;
-
-	/* Allocate and zero-init a struct ref_update */
-	update = xcalloc(1, sizeof(*update));
-	ALLOC_GROW(updates, updates_count + 1, updates_alloc);
-	updates[updates_count++] = update;
-
-	/* Store and reset accumulated options */
-	update->flags = update_flags;
-	update_flags = 0;
-
-	return update;
-}
-
-static void update_store_ref_name(struct ref_update *update,
-				  const char *ref_name)
-{
-	if (check_refname_format(ref_name, REFNAME_ALLOW_ONELEVEL))
-		die("invalid ref format: %s", ref_name);
-	update->ref_name = xstrdup(ref_name);
-}
-
-static void update_store_new_sha1(struct ref_update *update,
-				  const char *newvalue)
-{
-	if (*newvalue && get_sha1(newvalue, update->new_sha1))
-		die("invalid new value for ref %s: %s",
-		    update->ref_name, newvalue);
-}
-
-static void update_store_old_sha1(struct ref_update *update,
-				  const char *oldvalue)
-{
-	if (*oldvalue && get_sha1(oldvalue, update->old_sha1))
-		die("invalid old value for ref %s: %s",
-		    update->ref_name, oldvalue);
-
-	/* We have an old value if non-empty, or if empty without -z */
-	update->have_old = *oldvalue || line_termination;
-}
-
+/*
+ * Parse one whitespace- or NUL-terminated, possibly C-quoted argument
+ * and append the result to arg.  Return a pointer to the terminator.
+ * Die if there is an error in how the argument is C-quoted.  This
+ * function is only used if not -z.
+ */
 static const char *parse_arg(const char *next, struct strbuf *arg)
 {
-	/* Parse SP-terminated, possibly C-quoted argument */
-	if (*next != '"')
+	if (*next == '"') {
+		const char *orig = next;
+
+		if (unquote_c_style(arg, next, &next))
+			die("badly quoted argument: %s", orig);
+		if (*next && !isspace(*next))
+			die("unexpected character after quoted argument: %s", orig);
+	} else {
 		while (*next && !isspace(*next))
 			strbuf_addch(arg, *next++);
-	else if (unquote_c_style(arg, next, &next))
-		die("badly quoted argument: %s", next);
+	}
 
-	/* Return position after the argument */
 	return next;
 }
 
-static const char *parse_first_arg(const char *next, struct strbuf *arg)
+/*
+ * Parse the reference name immediately after "command SP".  If not
+ * -z, then handle C-quoting.  Return a pointer to a newly allocated
+ * string containing the name of the reference, or NULL if there was
+ * an error.  Update *next to point at the character that terminates
+ * the argument.  Die if C-quoting is malformed or the reference name
+ * is invalid.
+ */
+static char *parse_refname(struct strbuf *input, const char **next)
 {
-	/* Parse argument immediately after "command SP" */
-	strbuf_reset(arg);
+	struct strbuf ref = STRBUF_INIT;
+
 	if (line_termination) {
 		/* Without -z, use the next argument */
-		next = parse_arg(next, arg);
+		*next = parse_arg(*next, &ref);
 	} else {
-		/* With -z, use rest of first NUL-terminated line */
-		strbuf_addstr(arg, next);
-		next = next + arg->len;
+		/* With -z, use everything up to the next NUL */
+		strbuf_addstr(&ref, *next);
+		*next += ref.len;
 	}
-	return next;
+
+	if (!ref.len) {
+		strbuf_release(&ref);
+		return NULL;
+	}
+
+	if (check_refname_format(ref.buf, REFNAME_ALLOW_ONELEVEL))
+		die("invalid ref format: %s", ref.buf);
+
+	return strbuf_detach(&ref, NULL);
 }
 
-static const char *parse_next_arg(const char *next, struct strbuf *arg)
+/*
+ * The value being parsed is <oldvalue> (as opposed to <newvalue>; the
+ * difference affects which error messages are generated):
+ */
+#define PARSE_SHA1_OLD 0x01
+
+/*
+ * For backwards compatibility, accept an empty string for update's
+ * <newvalue> in binary mode to be equivalent to specifying zeros.
+ */
+#define PARSE_SHA1_ALLOW_EMPTY 0x02
+
+/*
+ * Parse an argument separator followed by the next argument, if any.
+ * If there is an argument, convert it to a SHA-1, write it to sha1,
+ * set *next to point at the character terminating the argument, and
+ * return 0.  If there is no argument at all (not even the empty
+ * string), return 1 and leave *next unchanged.  If the value is
+ * provided but cannot be converted to a SHA-1, die.  flags can
+ * include PARSE_SHA1_OLD and/or PARSE_SHA1_ALLOW_EMPTY.
+ */
+static int parse_next_sha1(struct strbuf *input, const char **next,
+			   unsigned char *sha1,
+			   const char *command, const char *refname,
+			   int flags)
 {
-	/* Parse next SP-terminated or NUL-terminated argument, if any */
-	strbuf_reset(arg);
+	struct strbuf arg = STRBUF_INIT;
+	int ret = 0;
+
+	if (*next == input->buf + input->len)
+		goto eof;
+
 	if (line_termination) {
 		/* Without -z, consume SP and use next argument */
-		if (!*next)
-			return NULL;
-		if (*next != ' ')
-			die("expected SP but got: %s", next);
-		next = parse_arg(next + 1, arg);
+		if (!**next || **next == line_termination)
+			return 1;
+		if (**next != ' ')
+			die("%s %s: expected SP but got: %s",
+			    command, refname, *next);
+		(*next)++;
+		*next = parse_arg(*next, &arg);
+		if (arg.len) {
+			if (get_sha1(arg.buf, sha1))
+				goto invalid;
+		} else {
+			/* Without -z, an empty value means all zeros: */
+			hashclr(sha1);
+		}
 	} else {
 		/* With -z, read the next NUL-terminated line */
-		if (*next)
-			die("expected NUL but got: %s", next);
-		if (strbuf_getline(arg, stdin, '\0') == EOF)
-			return NULL;
-		next = arg->buf + arg->len;
+		if (**next)
+			die("%s %s: expected NUL but got: %s",
+			    command, refname, *next);
+		(*next)++;
+		if (*next == input->buf + input->len)
+			goto eof;
+		strbuf_addstr(&arg, *next);
+		*next += arg.len;
+
+		if (arg.len) {
+			if (get_sha1(arg.buf, sha1))
+				goto invalid;
+		} else if (flags & PARSE_SHA1_ALLOW_EMPTY) {
+			/* With -z, treat an empty value as all zeros: */
+			warning("%s %s: missing <newvalue>, treating as zero",
+				command, refname);
+			hashclr(sha1);
+		} else {
+			/*
+			 * With -z, an empty non-required value means
+			 * unspecified:
+			 */
+			ret = 1;
+		}
 	}
-	return next;
-}
 
-static void parse_cmd_update(const char *next)
-{
-	struct strbuf ref = STRBUF_INIT;
-	struct strbuf newvalue = STRBUF_INIT;
-	struct strbuf oldvalue = STRBUF_INIT;
-	struct ref_update *update;
+	strbuf_release(&arg);
 
-	update = update_alloc();
+	return ret;
 
-	if ((next = parse_first_arg(next, &ref)) != NULL && ref.buf[0])
-		update_store_ref_name(update, ref.buf);
-	else
-		die("update line missing <ref>");
+ invalid:
+	die(flags & PARSE_SHA1_OLD ?
+	    "%s %s: invalid <oldvalue>: %s" :
+	    "%s %s: invalid <newvalue>: %s",
+	    command, refname, arg.buf);
+
+ eof:
+	die(flags & PARSE_SHA1_OLD ?
+	    "%s %s: unexpected end of input when reading <oldvalue>" :
+	    "%s %s: unexpected end of input when reading <newvalue>",
+	    command, refname);
+}
 
-	if ((next = parse_next_arg(next, &newvalue)) != NULL)
-		update_store_new_sha1(update, newvalue.buf);
-	else
-		die("update %s missing <newvalue>", ref.buf);
 
-	if ((next = parse_next_arg(next, &oldvalue)) != NULL)
-		update_store_old_sha1(update, oldvalue.buf);
-	else if(!line_termination)
-		die("update %s missing [<oldvalue>] NUL", ref.buf);
+/*
+ * The following five parse_cmd_*() functions parse the corresponding
+ * command.  In each case, next points at the character following the
+ * command name and the following space.  They each return a pointer
+ * to the character terminating the command, and die with an
+ * explanatory message if there are any parsing problems.  All of
+ * these functions handle either text or binary format input,
+ * depending on how line_termination is set.
+ */
+
+static const char *parse_cmd_update(struct strbuf *input, const char *next)
+{
+	char *refname;
+	unsigned char new_sha1[20];
+	unsigned char old_sha1[20];
+	int have_old;
+
+	refname = parse_refname(input, &next);
+	if (!refname)
+		die("update: missing <ref>");
+
+	if (parse_next_sha1(input, &next, new_sha1, "update", refname,
+			    PARSE_SHA1_ALLOW_EMPTY))
+		die("update %s: missing <newvalue>", refname);
+
+	have_old = !parse_next_sha1(input, &next, old_sha1, "update", refname,
+				    PARSE_SHA1_OLD);
+
+	if (*next != line_termination)
+		die("update %s: extra input: %s", refname, next);
+
+	if (ref_transaction_update(transaction, refname, new_sha1, old_sha1,
+				   update_flags, have_old, &err))
+		die("%s", err.buf);
+
+	update_flags = 0;
+	free(refname);
 
-	if (next && *next)
-		die("update %s has extra input: %s", ref.buf, next);
+	return next;
 }
 
-static void parse_cmd_create(const char *next)
+static const char *parse_cmd_create(struct strbuf *input, const char *next)
 {
-	struct strbuf ref = STRBUF_INIT;
-	struct strbuf newvalue = STRBUF_INIT;
-	struct ref_update *update;
+	char *refname;
+	unsigned char new_sha1[20];
 
-	update = update_alloc();
-	update->have_old = 1;
+	refname = parse_refname(input, &next);
+	if (!refname)
+		die("create: missing <ref>");
 
-	if ((next = parse_first_arg(next, &ref)) != NULL && ref.buf[0])
-		update_store_ref_name(update, ref.buf);
-	else
-		die("create line missing <ref>");
+	if (parse_next_sha1(input, &next, new_sha1, "create", refname, 0))
+		die("create %s: missing <newvalue>", refname);
 
-	if ((next = parse_next_arg(next, &newvalue)) != NULL)
-		update_store_new_sha1(update, newvalue.buf);
-	else
-		die("create %s missing <newvalue>", ref.buf);
-	if (is_null_sha1(update->new_sha1))
-		die("create %s given zero new value", ref.buf);
+	if (is_null_sha1(new_sha1))
+		die("create %s: zero <newvalue>", refname);
+
+	if (*next != line_termination)
+		die("create %s: extra input: %s", refname, next);
+
+	ref_transaction_create(transaction, refname, new_sha1, update_flags);
+
+	update_flags = 0;
+	free(refname);
 
-	if (next && *next)
-		die("create %s has extra input: %s", ref.buf, next);
+	return next;
 }
 
-static void parse_cmd_delete(const char *next)
+static const char *parse_cmd_delete(struct strbuf *input, const char *next)
 {
-	struct strbuf ref = STRBUF_INIT;
-	struct strbuf oldvalue = STRBUF_INIT;
-	struct ref_update *update;
+	char *refname;
+	unsigned char old_sha1[20];
+	int have_old;
+
+	refname = parse_refname(input, &next);
+	if (!refname)
+		die("delete: missing <ref>");
+
+	if (parse_next_sha1(input, &next, old_sha1, "delete", refname,
+			    PARSE_SHA1_OLD)) {
+		have_old = 0;
+	} else {
+		if (is_null_sha1(old_sha1))
+			die("delete %s: zero <oldvalue>", refname);
+		have_old = 1;
+	}
 
-	update = update_alloc();
+	if (*next != line_termination)
+		die("delete %s: extra input: %s", refname, next);
 
-	if ((next = parse_first_arg(next, &ref)) != NULL && ref.buf[0])
-		update_store_ref_name(update, ref.buf);
-	else
-		die("delete line missing <ref>");
+	ref_transaction_delete(transaction, refname, old_sha1,
+			       update_flags, have_old);
 
-	if ((next = parse_next_arg(next, &oldvalue)) != NULL)
-		update_store_old_sha1(update, oldvalue.buf);
-	else if(!line_termination)
-		die("delete %s missing [<oldvalue>] NUL", ref.buf);
-	if (update->have_old && is_null_sha1(update->old_sha1))
-		die("delete %s given zero old value", ref.buf);
+	update_flags = 0;
+	free(refname);
 
-	if (next && *next)
-		die("delete %s has extra input: %s", ref.buf, next);
+	return next;
 }
 
-static void parse_cmd_verify(const char *next)
+static const char *parse_cmd_verify(struct strbuf *input, const char *next)
 {
-	struct strbuf ref = STRBUF_INIT;
-	struct strbuf value = STRBUF_INIT;
-	struct ref_update *update;
+	char *refname;
+	unsigned char new_sha1[20];
+	unsigned char old_sha1[20];
+	int have_old;
+
+	refname = parse_refname(input, &next);
+	if (!refname)
+		die("verify: missing <ref>");
+
+	if (parse_next_sha1(input, &next, old_sha1, "verify", refname,
+			    PARSE_SHA1_OLD)) {
+		hashclr(new_sha1);
+		have_old = 0;
+	} else {
+		hashcpy(new_sha1, old_sha1);
+		have_old = 1;
+	}
 
-	update = update_alloc();
+	if (*next != line_termination)
+		die("verify %s: extra input: %s", refname, next);
 
-	if ((next = parse_first_arg(next, &ref)) != NULL && ref.buf[0])
-		update_store_ref_name(update, ref.buf);
-	else
-		die("verify line missing <ref>");
+	if (ref_transaction_update(transaction, refname, new_sha1, old_sha1,
+				   update_flags, have_old, &err))
+		die("%s", err.buf);
 
-	if ((next = parse_next_arg(next, &value)) != NULL) {
-		update_store_old_sha1(update, value.buf);
-		update_store_new_sha1(update, value.buf);
-	} else if(!line_termination)
-		die("verify %s missing [<oldvalue>] NUL", ref.buf);
+	update_flags = 0;
+	free(refname);
 
-	if (next && *next)
-		die("verify %s has extra input: %s", ref.buf, next);
+	return next;
 }
 
-static void parse_cmd_option(const char *next)
+static const char *parse_cmd_option(struct strbuf *input, const char *next)
 {
-	if (!strcmp(next, "no-deref"))
+	if (!strncmp(next, "no-deref", 8) && next[8] == line_termination)
 		update_flags |= REF_NODEREF;
 	else
 		die("option unknown: %s", next);
+	return next + 8;
 }
 
 static void update_refs_stdin(void)
 {
-	struct strbuf cmd = STRBUF_INIT;
+	struct strbuf input = STRBUF_INIT;
+	const char *next;
 
+	if (strbuf_read(&input, 0, 1000) < 0)
+		die_errno("could not read from stdin");
+	next = input.buf;
 	/* Read each line dispatch its command */
-	while (strbuf_getline(&cmd, stdin, line_termination) != EOF)
-		if (!cmd.buf[0])
+	while (next < input.buf + input.len) {
+		if (*next == line_termination)
 			die("empty command in input");
-		else if (isspace(*cmd.buf))
-			die("whitespace before command: %s", cmd.buf);
-		else if (starts_with(cmd.buf, "update "))
-			parse_cmd_update(cmd.buf + 7);
-		else if (starts_with(cmd.buf, "create "))
-			parse_cmd_create(cmd.buf + 7);
-		else if (starts_with(cmd.buf, "delete "))
-			parse_cmd_delete(cmd.buf + 7);
-		else if (starts_with(cmd.buf, "verify "))
-			parse_cmd_verify(cmd.buf + 7);
-		else if (starts_with(cmd.buf, "option "))
-			parse_cmd_option(cmd.buf + 7);
+		else if (isspace(*next))
+			die("whitespace before command: %s", next);
+		else if (starts_with(next, "update "))
+			next = parse_cmd_update(&input, next + 7);
+		else if (starts_with(next, "create "))
+			next = parse_cmd_create(&input, next + 7);
+		else if (starts_with(next, "delete "))
+			next = parse_cmd_delete(&input, next + 7);
+		else if (starts_with(next, "verify "))
+			next = parse_cmd_verify(&input, next + 7);
+		else if (starts_with(next, "option "))
+			next = parse_cmd_option(&input, next + 7);
 		else
-			die("unknown command: %s", cmd.buf);
+			die("unknown command: %s", next);
+
+		next++;
+	}
 
-	strbuf_release(&cmd);
+	strbuf_release(&input);
 }
 
 int cmd_update_ref(int argc, const char **argv, const char *prefix)
 {
 	const char *refname, *oldval, *msg = NULL;
 	unsigned char sha1[20], oldsha1[20];
