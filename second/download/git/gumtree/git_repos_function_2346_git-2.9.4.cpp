size_t quote_c_style(const char *name, struct strbuf *sb, FILE *fp, int nodq)
{
	return quote_c_style_counted(name, -1, sb, fp, nodq);
}