		need_tagged = 1;
	if (!strcmp(used_atom[at], "symref"))
		need_symref = 1;
	return at;
}

static void quote_formatting(struct strbuf *s, const char *str, int quote_style)
{
	switch (quote_style) {
	case QUOTE_NONE:
		strbuf_addstr(s, str);
		break;
	case QUOTE_SHELL:
		sq_quote_buf(s, str);
		break;
	case QUOTE_PERL:
		perl_quote_buf(s, str);
		break;
	case QUOTE_PYTHON:
		python_quote_buf(s, str);
		break;
	case QUOTE_TCL:
		tcl_quote_buf(s, str);
		break;
	}
}

static void append_atom(struct atom_value *v, struct ref_formatting_state *state)
{
	/*
	 * Quote formatting is only done when the stack has a single
	 * element. Otherwise quote formatting is done on the
	 * element's entire output strbuf when the %(end) atom is
	 * encountered.
	 */
	if (!state->stack->prev)
		quote_formatting(&state->stack->output, v->s, state->quote_style);
	else
		strbuf_addstr(&state->stack->output, v->s);
}

static void push_stack_element(struct ref_formatting_stack **stack)
{
	struct ref_formatting_stack *s = xcalloc(1, sizeof(struct ref_formatting_stack));

	strbuf_init(&s->output, 0);
	s->prev = *stack;
	*stack = s;
}

static void pop_stack_element(struct ref_formatting_stack **stack)
{
	struct ref_formatting_stack *current = *stack;
	struct ref_formatting_stack *prev = current->prev;

	if (prev)
		strbuf_addbuf(&prev->output, &current->output);
	strbuf_release(&current->output);
	free(current);
	*stack = prev;
}

static void end_align_handler(struct ref_formatting_stack *stack)
{
	struct align *align = (struct align *)stack->at_end_data;
	struct strbuf s = STRBUF_INIT;

	strbuf_utf8_align(&s, align->position, align->width, stack->output.buf);
	strbuf_swap(&stack->output, &s);
	strbuf_release(&s);
}

static void align_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state)
{
	struct ref_formatting_stack *new;

	push_stack_element(&state->stack);
	new = state->stack;
	new->at_end = end_align_handler;
	new->at_end_data = &atomv->u.align;
}

static void end_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state)
{
	struct ref_formatting_stack *current = state->stack;
	struct strbuf s = STRBUF_INIT;

	if (!current->at_end)
		die(_("format: %%(end) atom used without corresponding atom"));
	current->at_end(current);

	/*
	 * Perform quote formatting when the stack element is that of
	 * a supporting atom. If nested then perform quote formatting
	 * only on the topmost supporting atom.
	 */
	if (!state->stack->prev->prev) {
		quote_formatting(&s, current->output.buf, state->quote_style);
		strbuf_swap(&current->output, &s);
	}
	strbuf_release(&s);
	pop_stack_element(&state->stack);
}

static int match_atom_name(const char *name, const char *atom_name, const char **val)
{
	const char *body;

	if (!skip_prefix(name, atom_name, &body))
		return 0; /* doesn't even begin with "atom_name" */
	if (!body[0]) {
		*val = NULL; /* %(atom_name) and no customization */
		return 1;
	}
	if (body[0] != ':')
		return 0; /* "atom_namefoo" is not "atom_name" or "atom_name:..." */
	*val = body + 1; /* "atom_name:val" */
	return 1;
}

/*
 * In a format string, find the next occurrence of %(atom).
 */
static const char *find_next(const char *cp)
{
	while (*cp) {
