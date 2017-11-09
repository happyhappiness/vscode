static int is_mboxrd_from(const char *line, int len)
{
	/*
	 * a line matching /^From $/ here would only have len == 4
	 * at this point because is_empty_line would've trimmed all
	 * trailing space
	 */
	return len > 4 && starts_with(line + strspn(line, ">"), "From ");
}