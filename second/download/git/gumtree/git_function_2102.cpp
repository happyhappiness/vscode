static int fsck_error_func(struct object *obj, int type, const char *err, ...)
{
	va_list params;
	va_start(params, err);
	objreport(obj, (type == FSCK_WARN) ? "warning" : "error", err, params);
	va_end(params);
	return (type == FSCK_WARN) ? 0 : 1;
}