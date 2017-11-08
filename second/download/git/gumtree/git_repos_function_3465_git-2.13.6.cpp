int rerere(int flags)
{
	struct string_list merge_rr = STRING_LIST_INIT_DUP;
	int fd, status;

	fd = setup_rerere(&merge_rr, flags);
	if (fd < 0)
		return 0;
	status = do_plain_rerere(&merge_rr, fd);
	free_rerere_dirs();
	return status;
}