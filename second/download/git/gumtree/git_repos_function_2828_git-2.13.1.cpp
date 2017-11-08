static void update_abort_safety_file(void)
{
	struct object_id head;

	/* Do nothing on a single-pick */
	if (!file_exists(git_path_seq_dir()))
		return;

	if (!get_oid("HEAD", &head))
		write_file(git_path_abort_safety_file(), "%s", oid_to_hex(&head));
	else
		write_file(git_path_abort_safety_file(), "%s", "");
}