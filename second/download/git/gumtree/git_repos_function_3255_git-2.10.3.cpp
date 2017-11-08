static int handle_modify_delete(struct merge_options *o,
				 const char *path,
				 struct object_id *o_oid, int o_mode,
				 struct object_id *a_oid, int a_mode,
				 struct object_id *b_oid, int b_mode)
{
	return handle_change_delete(o,
				    path,
				    o_oid, o_mode,
				    a_oid, a_mode,
				    b_oid, b_mode,
				    _("modify"), _("modified"));
}