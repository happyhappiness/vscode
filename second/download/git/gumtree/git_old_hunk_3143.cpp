
static int grep_cmd_config(const char *var, const char *value, void *cb)
{
	int st = grep_config(var, value, cb);
	if (git_color_default_config(var, value, cb) < 0)
		st = -1;
	return st;
}

static void *lock_and_read_sha1_file(const unsigned char *sha1, enum object_type *type, unsigned long *size)
{
	void *data;
