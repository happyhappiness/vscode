void color_print_strbuf(FILE *fp, const char *color, const struct strbuf *sb)
{
	if (*color)
		fprintf(fp, "%s", color);
	fprintf(fp, "%s", sb->buf);
	if (*color)
		fprintf(fp, "%s", GIT_COLOR_RESET);
}