const char *git_author_info(int flag)
{
	if (getenv("GIT_AUTHOR_NAME"))
		author_ident_explicitly_given |= IDENT_NAME_GIVEN;
	if (getenv("GIT_AUTHOR_EMAIL"))
		author_ident_explicitly_given |= IDENT_MAIL_GIVEN;
	return fmt_ident(getenv("GIT_AUTHOR_NAME"),
			 getenv("GIT_AUTHOR_EMAIL"),
			 getenv("GIT_AUTHOR_DATE"),
			 flag);
}