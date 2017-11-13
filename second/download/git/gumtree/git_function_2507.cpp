static void print_value(struct atom_value *v, int quote_style)
{
	struct strbuf sb = STRBUF_INIT;
	switch (quote_style) {
	case QUOTE_NONE:
		fputs(v->s, stdout);
		break;
	case QUOTE_SHELL:
		sq_quote_buf(&sb, v->s);
		break;
	case QUOTE_PERL:
		perl_quote_buf(&sb, v->s);
		break;
	case QUOTE_PYTHON:
		python_quote_buf(&sb, v->s);
		break;
	case QUOTE_TCL:
		tcl_quote_buf(&sb, v->s);
		break;
	}
	if (quote_style != QUOTE_NONE) {
		fputs(sb.buf, stdout);
		strbuf_release(&sb);
	}
}