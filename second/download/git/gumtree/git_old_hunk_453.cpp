
	fflush(NULL);
	if (start_async(&async))
		return 0;	/* error was already reported */

	if (strbuf_read(&nbuf, async.out, len) < 0) {
		error("read from external filter %s failed", cmd);
		ret = 0;
	}
	if (close(async.out)) {
		error("read from external filter %s failed", cmd);
		ret = 0;
	}
	if (finish_async(&async)) {
		error("external filter %s failed", cmd);
		ret = 0;
	}

	if (ret) {
		strbuf_swap(dst, &nbuf);
	}
	strbuf_release(&nbuf);
	return ret;
}

static struct convert_driver {
	const char *name;
	struct convert_driver *next;
	const char *smudge;
	const char *clean;
	int required;
} *user_convert, **user_convert_tail;

static int read_convert_config(const char *var, const char *value, void *cb)
{
	const char *key, *name;
	int namelen;
	struct convert_driver *drv;

