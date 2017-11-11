void alloc_report(void)
{
	REPORT(blob, struct blob);
	REPORT(tree, struct tree);
	REPORT(commit, struct commit);
	REPORT(tag, struct tag);
	REPORT(object, union any_object);
}