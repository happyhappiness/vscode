const char *branch_get_push(struct branch *branch, struct strbuf *err)
{
	if (!branch->push_tracking_ref)
		branch->push_tracking_ref = branch_get_push_1(branch, err);
	return branch->push_tracking_ref;
}