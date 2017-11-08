static void set_ident_var(char **buf, char *val)
{
	free(*buf);
	*buf = val;
}