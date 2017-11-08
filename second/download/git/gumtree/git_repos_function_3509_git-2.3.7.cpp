void argv_array_pushl(struct argv_array *array, ...)
{
	va_list ap;
	const char *arg;

	va_start(ap, array);
	while((arg = va_arg(ap, const char *)))
		argv_array_push(array, arg);
	va_end(ap);
}