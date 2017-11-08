int cmd2process_cmp(const void *unused_cmp_data,
		    const struct subprocess_entry *e1,
		    const struct subprocess_entry *e2,
		    const void *unused_keydata)
{
	return strcmp(e1->cmd, e2->cmd);
}