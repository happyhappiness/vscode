static int ll_ext_merge(const struct ll_merge_driver *fn,
			mmbuffer_t *result,
			const char *path,
			mmfile_t *orig, const char *orig_name,
			mmfile_t *src1, const char *name1,
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
	create_temp(orig, temp[0]);
	create_temp(src1, temp[1]);
	create_temp(src2, temp[2]);
	sprintf(temp[3], "%d", marker_size);

	strbuf_expand(&cmd, fn->cmdline, strbuf_expand_dict_cb, &dict);

	args[0] = cmd.buf;
	status = run_command_v_opt(args, RUN_USING_SHELL);
	fd = open(temp[1], O_RDONLY);
	if (fd < 0)
		goto bad;
	if (fstat(fd, &st))
		goto close_bad;
	result->size = st.st_size;
	result->ptr = xmalloc(result->size + 1);
	if (read_in_full(fd, result->ptr, result->size) != result->size) {
		free(result->ptr);
		result->ptr = NULL;
		result->size = 0;
	}
 close_bad:
	close(fd);
 bad:
	for (i = 0; i < 3; i++)
		unlink_or_warn(temp[i]);
	strbuf_release(&cmd);
	strbuf_release(&path_sq);
	return status;
}