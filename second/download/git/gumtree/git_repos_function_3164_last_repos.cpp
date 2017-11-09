static void convert_attrs(struct conv_attrs *ca, const char *path)
{
	static struct attr_check *check;

	if (!check) {
		check = attr_check_initl("crlf", "ident", "filter",
					 "eol", "text", NULL);
		user_convert_tail = &user_convert;
		git_config(read_convert_config, NULL);
	}

	if (!git_check_attr(path, check)) {
		struct attr_check_item *ccheck = check->items;
		ca->crlf_action = git_path_check_crlf(ccheck + 4);
		if (ca->crlf_action == CRLF_UNDEFINED)
			ca->crlf_action = git_path_check_crlf(ccheck + 0);
		ca->attr_action = ca->crlf_action;
		ca->ident = git_path_check_ident(ccheck + 1);
		ca->drv = git_path_check_convert(ccheck + 2);
		if (ca->crlf_action != CRLF_BINARY) {
			enum eol eol_attr = git_path_check_eol(ccheck + 3);
			if (ca->crlf_action == CRLF_AUTO && eol_attr == EOL_LF)
				ca->crlf_action = CRLF_AUTO_INPUT;
			else if (ca->crlf_action == CRLF_AUTO && eol_attr == EOL_CRLF)
				ca->crlf_action = CRLF_AUTO_CRLF;
			else if (eol_attr == EOL_LF)
				ca->crlf_action = CRLF_TEXT_INPUT;
			else if (eol_attr == EOL_CRLF)
				ca->crlf_action = CRLF_TEXT_CRLF;
		}
		ca->attr_action = ca->crlf_action;
	} else {
		ca->drv = NULL;
		ca->crlf_action = CRLF_UNDEFINED;
		ca->ident = 0;
	}
	if (ca->crlf_action == CRLF_TEXT)
		ca->crlf_action = text_eol_is_crlf() ? CRLF_TEXT_CRLF : CRLF_TEXT_INPUT;
	if (ca->crlf_action == CRLF_UNDEFINED && auto_crlf == AUTO_CRLF_FALSE)
		ca->crlf_action = CRLF_BINARY;
	if (ca->crlf_action == CRLF_UNDEFINED && auto_crlf == AUTO_CRLF_TRUE)
		ca->crlf_action = CRLF_AUTO_CRLF;
	if (ca->crlf_action == CRLF_UNDEFINED && auto_crlf == AUTO_CRLF_INPUT)
		ca->crlf_action = CRLF_AUTO_INPUT;
}