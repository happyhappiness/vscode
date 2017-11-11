static void setup_whitespace_attr_check(struct git_attr_check *check)
{
	static struct git_attr *attr_whitespace;

	if (!attr_whitespace)
		attr_whitespace = git_attr("whitespace");
	check[0].attr = attr_whitespace;
}