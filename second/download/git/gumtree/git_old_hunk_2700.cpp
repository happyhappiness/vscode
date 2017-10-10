
static int external_specification_len(const char *url)
{
	return strchr(url, ':') - url;
}

struct transport *transport_get(struct remote *remote, const char *url)
{
	const char *helper;
	struct transport *ret = xcalloc(1, sizeof(*ret));

	ret->progress = isatty(2);
