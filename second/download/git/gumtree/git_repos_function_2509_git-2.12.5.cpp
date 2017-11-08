int strbuf_getline_nul(struct strbuf *sb, FILE *fp)
{
	return strbuf_getdelim(sb, fp, '\0');
}