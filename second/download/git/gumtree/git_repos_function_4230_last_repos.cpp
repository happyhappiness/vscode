static int check_attr_export_ignore(const struct attr_check *check)
{
	return check && ATTR_TRUE(check->items[0].value);
}