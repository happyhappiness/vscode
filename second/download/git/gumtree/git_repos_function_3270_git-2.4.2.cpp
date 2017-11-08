static void setup_archive_check(struct git_attr_check *check)
{
	static struct git_attr *attr_export_ignore;
	static struct git_attr *attr_export_subst;

	if (!attr_export_ignore) {
		attr_export_ignore = git_attr("export-ignore");
		attr_export_subst = git_attr("export-subst");
	}
	check[0].attr = attr_export_ignore;
	check[1].attr = attr_export_subst;
}