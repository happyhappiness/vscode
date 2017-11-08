static void convert_attrs(struct conv_attrs *ca, const char *path)
{
	int i;
	static struct git_attr_check ccheck[NUM_CONV_ATTRS];

	if (!ccheck[0].attr) {
		for (i = 0; i < NUM_CONV_ATTRS; i++)
			ccheck[i].attr = git_attr(conv_attr_name[i]);
		user_convert_tail = &user_convert;
		git_config(read_convert_config, NULL);
	}

	if (!git_check_attr(path, NUM_CONV_ATTRS, ccheck)) {
		ca->crlf_action = git_path_check_crlf(path, ccheck + 4);
		if (ca->crlf_action == CRLF_GUESS)
			ca->crlf_action = git_path_check_crlf(path, ccheck + 0);
		ca->ident = git_path_check_ident(path, ccheck + 1);
		ca->drv = git_path_check_convert(path, ccheck + 2);
		ca->eol_attr = git_path_check_eol(path, ccheck + 3);
	} else {
		ca->drv = NULL;
		ca->crlf_action = CRLF_GUESS;
		ca->eol_attr = EOL_UNSET;
		ca->ident = 0;
	}
}