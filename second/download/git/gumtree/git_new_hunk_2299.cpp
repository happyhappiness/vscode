			mmfile_t *src2, const char *name2,
			const struct ll_merge_options *opts,
			int marker_size)
{
	char temp[4][50];
	struct strbuf cmd = STRBUF_INIT;
	struct strbuf_expand_dict_entry dict[6];
	struct strbuf path_sq = STRBUF_INIT;
	const char *args[] = { NULL, NULL };
	int status, fd, i;
	struct stat st;
	assert(opts);

	sq_quote_buf(&path_sq, path);
	dict[0].placeholder = "O"; dict[0].value = temp[0];
	dict[1].placeholder = "A"; dict[1].value = temp[1];
	dict[2].placeholder = "B"; dict[2].value = temp[2];
	dict[3].placeholder = "L"; dict[3].value = temp[3];
	dict[4].placeholder = "P"; dict[4].value = path_sq.buf;
	dict[5].placeholder = NULL; dict[5].value = NULL;

	if (fn->cmdline == NULL)
		die("custom merge driver %s lacks command line.", fn->name);

	result->ptr = NULL;
	result->size = 0;
