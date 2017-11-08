static void handle_modify_delete(struct merge_options *o,
				 const char *path,
				 unsigned char *o_sha, int o_mode,
				 unsigned char *a_sha, int a_mode,
				 unsigned char *b_sha, int b_mode)
{
	handle_change_delete(o,
			     path,
			     o_sha, o_mode,
			     a_sha, a_mode,
			     b_sha, b_mode,
			     _("modify"), _("modified"));
}