int strbuf_getline_lf(struct strbuf *sb, FILE *fp)
{
	return strbuf_getdelim(sb, fp, '\n');
}