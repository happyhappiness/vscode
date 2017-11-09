uid_t recv_user_name(int f, uid_t uid)
{
	struct idlist *node;
	int len = read_byte(f);
	char *name = new_array(char, len+1);
	if (!name)
		out_of_memory("recv_user_name");
	read_sbuf(f, name, len);
	if (numeric_ids < 0) {
		free(name);
		name = NULL;
	}
	node = recv_add_id(&uidlist, uidmap, uid, name); /* node keeps name's memory */
	return node->id2;
}