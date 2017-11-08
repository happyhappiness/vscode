static int handle_modify_delete(struct merge_options *o,
				 const char *path,
				 struct object_id *o_oid, int o_mode,
				 struct object_id *a_oid, int a_mode,
				 struct object_id *b_oid, int b_mode)
{
	const char *modify_branch, *delete_branch;
	struct object_id *changed_oid;
	int changed_mode;

	if (a_oid) {
		modify_branch = o->branch1;
		delete_branch = o->branch2;
		changed_oid = a_oid;
		changed_mode = a_mode;
	} else {
		modify_branch = o->branch2;
		delete_branch = o->branch1;
		changed_oid = b_oid;
		changed_mode = b_mode;
	}

	return handle_change_delete(o,
				    path, NULL,
				    o_oid, o_mode,
				    changed_oid, changed_mode,
				    modify_branch, delete_branch,
				    _("modify"), _("modified"));
}