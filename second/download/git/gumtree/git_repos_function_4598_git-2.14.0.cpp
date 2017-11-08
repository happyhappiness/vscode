const char *git_committer_info(int flag)
{
	if (getenv("GIT_COMMITTER_NAME"))
		committer_ident_explicitly_given |= IDENT_NAME_GIVEN;
	if (getenv("GIT_COMMITTER_EMAIL"))
		committer_ident_explicitly_given |= IDENT_MAIL_GIVEN;
	return fmt_ident(getenv("GIT_COMMITTER_NAME"),
			 getenv("GIT_COMMITTER_EMAIL"),
			 getenv("GIT_COMMITTER_DATE"),
			 flag);
}