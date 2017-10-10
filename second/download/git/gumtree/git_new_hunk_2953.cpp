
	if (fn->cmdline == NULL)
		die("custom merge driver %s lacks command line.", fn->name);

	result->ptr = NULL;
	result->size = 0;
	create_temp(orig, temp[0], sizeof(temp[0]));
	create_temp(src1, temp[1], sizeof(temp[1]));
	create_temp(src2, temp[2], sizeof(temp[2]));
	xsnprintf(temp[3], sizeof(temp[3]), "%d", marker_size);

	strbuf_expand(&cmd, fn->cmdline, strbuf_expand_dict_cb, &dict);

	args[0] = cmd.buf;
	status = run_command_v_opt(args, RUN_USING_SHELL);
	fd = open(temp[1], O_RDONLY);
