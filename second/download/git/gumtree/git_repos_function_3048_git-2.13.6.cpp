static int git_path_check_ident(struct attr_check_item *check)
{
	const char *value = check->value;

	return !!ATTR_TRUE(value);
}