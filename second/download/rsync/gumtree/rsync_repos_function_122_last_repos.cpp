gid_t recv_group_name(int f, gid_t gid, uint16 *flags_ptr)
{
	struct idlist *node;
	int len = read_byte(f);
	char *name = new_array(char, len+1);
	if (!name)
		out_of_memory("recv_group_name");
	read_sbuf(f, name, len);
	if (numeric_ids < 0) {
		free(name);
		name = NULL;
	}
	node = recv_add_id(&gidlist, gidmap, gid, name); /* node keeps name's memory */
	if (flags_ptr && node->flags & FLAG_SKIP_GROUP)
		*flags_ptr |= FLAG_SKIP_GROUP;
	return node->id2;
}