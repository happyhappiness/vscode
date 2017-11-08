static int die_is_recursing_builtin(void)
{
	static int dying;
	return dying++;
}