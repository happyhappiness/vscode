void show_ref_array_item(struct ref_array_item *info, const char *format, int quote_style)
{
	const char *cp, *sp, *ep;
	struct strbuf *final_buf;
	struct ref_formatting_state state = REF_FORMATTING_STATE_INIT;

	state.quote_style = quote_style;
	push_stack_element(&state.stack);

	for (cp = format; *cp && (sp = find_next(cp)); cp = ep + 1) {
		struct atom_value *atomv;

		ep = strchr(sp, ')');
		if (cp < sp)
			append_literal(cp, sp, &state);
		get_ref_atom_value(info, parse_ref_filter_atom(sp + 2, ep), &atomv);
		atomv->handler(atomv, &state);
	}
	if (*cp) {
		sp = cp + strlen(cp);
		append_literal(cp, sp, &state);
	}
	if (need_color_reset_at_eol) {
		struct atom_value resetv;
		char color[COLOR_MAXLEN] = "";

		if (color_parse("reset", color) < 0)
			die("BUG: couldn't parse 'reset' as a color");
		resetv.s = color;
		append_atom(&resetv, &state);
	}
	if (state.stack->prev)
		die(_("format: %%(end) atom missing"));
	final_buf = &state.stack->output;
	fwrite(final_buf->buf, 1, final_buf->len, stdout);
	pop_stack_element(&state.stack);
	putchar('\n');
}