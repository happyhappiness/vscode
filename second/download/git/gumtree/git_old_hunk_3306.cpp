{
	if (!branch || i < 0 || i >= branch->merge_nr)
		return 0;
	return refname_match(branch->merge[i]->src, refname);
}

__attribute((format (printf,2,3)))
static const char *error_buf(struct strbuf *err, const char *fmt, ...)
{
	if (err) {
		va_list ap;
		va_start(ap, fmt);
		strbuf_vaddf(err, fmt, ap);
