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