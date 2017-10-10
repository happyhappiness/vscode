
#define ERRORMSG(o,type) \
	( ((o) && (o)->msgs[(type)]) \
	  ? ((o)->msgs[(type)])      \
	  : (unpack_plumbing_errors[(type)]) )

static const char *super_prefixed(const char *path)
{
	/*
	 * It is necessary and sufficient to have two static buffers
	 * here, as the return value of this function is fed to
	 * error() using the unpack_*_errors[] templates we see above.
	 */
	static struct strbuf buf[2] = {STRBUF_INIT, STRBUF_INIT};
	static int super_prefix_len = -1;
	static unsigned idx = ARRAY_SIZE(buf) - 1;

	if (super_prefix_len < 0) {
		const char *super_prefix = get_super_prefix();
		if (!super_prefix) {
			super_prefix_len = 0;
		} else {
			int i;
			for (i = 0; i < ARRAY_SIZE(buf); i++)
				strbuf_addstr(&buf[i], super_prefix);
			super_prefix_len = buf[0].len;
		}
	}

	if (!super_prefix_len)
		return path;

	if (++idx >= ARRAY_SIZE(buf))
		idx = 0;

	strbuf_setlen(&buf[idx], super_prefix_len);
	strbuf_addstr(&buf[idx], path);

	return buf[idx].buf;
}

void setup_unpack_trees_porcelain(struct unpack_trees_options *opts,
				  const char *cmd)
{
	int i;
	const char **msgs = opts->msgs;
	const char *msg;
