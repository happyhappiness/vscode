void argv_array_push(struct argv_array *array, const char *value)
{
	argv_array_push_nodup(array, xstrdup(value));
}