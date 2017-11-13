static int objerror(struct object *obj, const char *err, ...)
{
	va_list params;
	va_start(params, err);
	errors_found |= ERROR_OBJECT;
	objreport(obj, "error", err, params);
	va_end(params);
	return -1;
}