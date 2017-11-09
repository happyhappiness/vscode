void argv_array_pushv(struct argv_array *array, const char **argv)
{
	for (; *argv; argv++)
		argv_array_push(array, *argv);
}