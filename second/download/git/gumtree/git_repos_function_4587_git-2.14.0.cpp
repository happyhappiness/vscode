const char *ident_default_name(void)
{
	if (!(ident_config_given & IDENT_NAME_GIVEN) && !git_default_name.len) {
		copy_gecos(xgetpwuid_self(&default_name_is_bogus), &git_default_name);
		strbuf_trim(&git_default_name);
	}
	return git_default_name.buf;
}