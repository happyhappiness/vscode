static int split_msg(struct strbuf *all_msgs, struct strbuf *msg, int *ofs)
{
	char *p, *data;
	size_t len;

	if (*ofs >= all_msgs->len)
		return 0;

	data = &all_msgs->buf[*ofs];
	len = all_msgs->len - *ofs;

	if (len < 5 || !starts_with(data, "From "))
		return 0;

	p = strchr(data, '\n');
	if (p) {
		p++;
		len -= p - data;
		*ofs += p - data;
		data = p;
	}

	p = strstr(data, "\nFrom ");
	if (p)
		len = &p[1] - data;

	strbuf_add(msg, data, len);
	*ofs += len;
	return 1;
}