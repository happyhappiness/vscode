 			return s[i];
 	return '\0';
 }
 
 static void print_tok_val(FILE *outfile, const char *tok, const char *val)
 {
-	char c = last_non_space_char(tok);
+	char c;
+
+	if (!tok) {
+		fprintf(outfile, "%s\n", val);
+		return;
+	}
+
+	c = last_non_space_char(tok);
 	if (!c)
 		return;
 	if (strchr(separators, c))
 		fprintf(outfile, "%s%s\n", tok, val);
 	else
 		fprintf(outfile, "%s%c %s\n", tok, separators[0], val);
 }
 
-static void print_all(FILE *outfile, struct trailer_item *first, int trim_empty)
+static void print_all(FILE *outfile, struct list_head *head, int trim_empty)
 {
+	struct list_head *pos;
 	struct trailer_item *item;
-	for (item = first; item; item = item->next) {
+	list_for_each(pos, head) {
+		item = list_entry(pos, struct trailer_item, list);
 		if (!trim_empty || strlen(item->value) > 0)
 			print_tok_val(outfile, item->token, item->value);
 	}
 }
 
-static void update_last(struct trailer_item **last)
-{
-	if (*last)
-		while ((*last)->next != NULL)
-			*last = (*last)->next;
-}
-
-static void update_first(struct trailer_item **first)
+static struct trailer_item *trailer_from_arg(struct arg_item *arg_tok)
 {
-	if (*first)
-		while ((*first)->previous != NULL)
-			*first = (*first)->previous;
+	struct trailer_item *new = xcalloc(sizeof(*new), 1);
+	new->token = arg_tok->token;
+	new->value = arg_tok->value;
+	arg_tok->token = arg_tok->value = NULL;
+	free_arg_item(arg_tok);
+	return new;
 }
 
 static void add_arg_to_input_list(struct trailer_item *on_tok,
-				  struct trailer_item *arg_tok,
-				  struct trailer_item **first,
-				  struct trailer_item **last)
-{
-	if (after_or_end(arg_tok->conf.where)) {
-		arg_tok->next = on_tok->next;
-		on_tok->next = arg_tok;
-		arg_tok->previous = on_tok;
-		if (arg_tok->next)
-			arg_tok->next->previous = arg_tok;
-		update_last(last);
-	} else {
-		arg_tok->previous = on_tok->previous;
-		on_tok->previous = arg_tok;
-		arg_tok->next = on_tok;
-		if (arg_tok->previous)
-			arg_tok->previous->next = arg_tok;
-		update_first(first);
-	}
+				  struct arg_item *arg_tok)
+{
+	int aoe = after_or_end(arg_tok->conf.where);
+	struct trailer_item *to_add = trailer_from_arg(arg_tok);
+	if (aoe)
+		list_add(&to_add->list, &on_tok->list);
+	else
+		list_add_tail(&to_add->list, &on_tok->list);
 }
 
 static int check_if_different(struct trailer_item *in_tok,
-			      struct trailer_item *arg_tok,
-			      int check_all)
+			      struct arg_item *arg_tok,
+			      int check_all,
+			      struct list_head *head)
 {
 	enum action_where where = arg_tok->conf.where;
+	struct list_head *next_head;
 	do {
-		if (!in_tok)
-			return 1;
 		if (same_trailer(in_tok, arg_tok))
 			return 0;
 		/*
 		 * if we want to add a trailer after another one,
 		 * we have to check those before this one
 		 */
-		in_tok = after_or_end(where) ? in_tok->previous : in_tok->next;
+		next_head = after_or_end(where) ? in_tok->list.prev
+						: in_tok->list.next;
+		if (next_head == head)
+			break;
+		in_tok = list_entry(next_head, struct trailer_item, list);
 	} while (check_all);
 	return 1;
 }
 
-static void remove_from_list(struct trailer_item *item,
-			     struct trailer_item **first,
-			     struct trailer_item **last)
-{
-	struct trailer_item *next = item->next;
-	struct trailer_item *previous = item->previous;
-
-	if (next) {
-		item->next->previous = previous;
-		item->next = NULL;
-	} else if (last)
-		*last = previous;
-
-	if (previous) {
-		item->previous->next = next;
-		item->previous = NULL;
-	} else if (first)
-		*first = next;
-}
-
-static struct trailer_item *remove_first(struct trailer_item **first)
-{
-	struct trailer_item *item = *first;
-	*first = item->next;
-	if (item->next) {
-		item->next->previous = NULL;
-		item->next = NULL;
-	}
-	return item;
-}
-
-static const char *apply_command(const char *command, const char *arg)
+static char *apply_command(const char *command, const char *arg)
 {
 	struct strbuf cmd = STRBUF_INIT;
 	struct strbuf buf = STRBUF_INIT;
 	struct child_process cp = CHILD_PROCESS_INIT;
 	const char *argv[] = {NULL, NULL};
-	const char *result;
+	char *result;
 
 	strbuf_addstr(&cmd, command);
 	if (arg)
 		strbuf_replace(&cmd, TRAILER_ARG_STRING, arg);
 
 	argv[0] = cmd.buf;
