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

void pretty_print_ref(const char *name, const unsigned char *sha1,
		const char *format)
{
