static int git_path_check_ident(struct git_attr_check *check)
{
	const char *value = check->value;

	return !!ATTR_TRUE(value);
}