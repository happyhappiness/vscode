static int slurp_attr(const char *line, const char *name, struct strbuf *attr)
{
	const char *ends, *ap = strcasestr(line, name);
	size_t sz;

	strbuf_setlen(attr, 0);
	if (!ap)
		return 0;
	ap += strlen(name);
	if (*ap == '"') {
		ap++;
		ends = "\"";
	}
	else
		ends = "; \t";
	sz = strcspn(ap, ends);
	strbuf_add(attr, ap, sz);
	return 1;
}