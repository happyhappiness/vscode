static const char *get_rev_name(const struct object *o, struct strbuf *buf)
{
	struct rev_name *n;
	struct commit *c;

	if (o->type != OBJ_COMMIT)
		return get_exact_ref_match(o);
	c = (struct commit *) o;
	n = c->util;
	if (!n)
		return NULL;

	if (!n->generation)
		return n->tip_name;
	else {
		int len = strlen(n->tip_name);
		if (len > 2 && !strcmp(n->tip_name + len - 2, "^0"))
			len -= 2;
		strbuf_reset(buf);
		strbuf_addf(buf, "%.*s~%d", len, n->tip_name, n->generation);
		return buf->buf;
	}
}