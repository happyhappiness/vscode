static int check_attr_export_subst(const struct attr_check *check)
{
	return check && ATTR_TRUE(check->items[1].value);
}