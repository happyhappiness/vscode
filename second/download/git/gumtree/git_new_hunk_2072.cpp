{
	int mode1 = 0, mode2 = 0;

	if (get_mode(name1, &mode1) || get_mode(name2, &mode2))
		return -1;

	if (mode1 && mode2 && S_ISDIR(mode1) != S_ISDIR(mode2))
		return error("file/directory conflict: %s, %s", name1, name2);

	if (S_ISDIR(mode1) || S_ISDIR(mode2)) {
		struct strbuf buffer1 = STRBUF_INIT;
		struct strbuf buffer2 = STRBUF_INIT;
		struct string_list p1 = STRING_LIST_INIT_DUP;
		struct string_list p2 = STRING_LIST_INIT_DUP;
