static char *substitute_branch_name(const char **string, int *len)
{
	struct strbuf buf = STRBUF_INIT;
	int ret = interpret_branch_name(*string, *len, &buf, 0);

	if (ret == *len) {
		size_t size;
		*string = strbuf_detach(&buf, &size);
		*len = size;
		return (char *)*string;
	}

	return NULL;
}