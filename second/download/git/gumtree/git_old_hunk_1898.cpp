	cb->warned_bad_reflog = 0;
	cb->name_for_errormsg = path;
	for_each_reflog_ent(path, handle_one_reflog_ent, cb_data);
	return 0;
}

static void handle_reflog(struct rev_info *revs, unsigned flags)
{
	struct all_refs_cb cb;
	cb.all_revs = revs;
	cb.all_flags = flags;
	for_each_reflog(handle_one_reflog, &cb);
}

static int add_parents_only(struct rev_info *revs, const char *arg_, int flags)
{
	unsigned char sha1[20];
	struct object *it;
	struct commit *commit;
	struct commit_list *parents;
