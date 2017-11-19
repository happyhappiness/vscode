static void say_patch_name(FILE *output, const char *fmt, struct patch *patch)
{
	struct strbuf sb = STRBUF_INIT;

	if (patch->old_name && patch->new_name &&
	    strcmp(patch->old_name, patch->new_name)) {
		quote_c_style(patch->old_name, &sb, NULL, 0);
		strbuf_addstr(&sb, " => ");
		quote_c_style(patch->new_name, &sb, NULL, 0);
	} else {
		const char *n = patch->new_name;
		if (!n)
			n = patch->old_name;
		quote_c_style(n, &sb, NULL, 0);
	}
	fprintf(output, fmt, sb.buf);
	fputc('\n', output);
	strbuf_release(&sb);
}