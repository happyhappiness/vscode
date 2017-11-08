const char *ident_default_email(void)
{
	if (!(ident_config_given & IDENT_MAIL_GIVEN) && !git_default_email.len) {
		const char *email = getenv("EMAIL");

		if (email && email[0]) {
			strbuf_addstr(&git_default_email, email);
			committer_ident_explicitly_given |= IDENT_MAIL_GIVEN;
			author_ident_explicitly_given |= IDENT_MAIL_GIVEN;
		} else
			copy_email(xgetpwuid_self(&default_email_is_bogus),
				   &git_default_email, &default_email_is_bogus);
		strbuf_trim(&git_default_email);
	}
	return git_default_email.buf;
}