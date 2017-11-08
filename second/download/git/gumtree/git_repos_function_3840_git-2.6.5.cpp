const char *fmt_name(const char *name, const char *email)
{
	return fmt_ident(name, email, NULL, IDENT_STRICT | IDENT_NO_DATE);
}