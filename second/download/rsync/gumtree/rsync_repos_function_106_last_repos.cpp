void set_allow_inc_recurse(void)
{
	client_info = shell_cmd ? shell_cmd : "";

	if (!recurse || use_qsort)
		allow_inc_recurse = 0;
	else if (!am_sender
	 && (delete_before || delete_after
	  || delay_updates || prune_empty_dirs))
		allow_inc_recurse = 0;
	else if (am_server && !local_server
	 && (strchr(client_info, 'i') == NULL))
		allow_inc_recurse = 0;
}