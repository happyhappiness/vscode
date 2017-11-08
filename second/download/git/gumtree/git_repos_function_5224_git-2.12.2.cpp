static int fsck_error_func(struct fsck_options *o,
	struct object *obj, int type, const char *message)
{
	objreport(obj, (type == FSCK_WARN) ? "warning" : "error", message);
	return (type == FSCK_WARN) ? 0 : 1;
}