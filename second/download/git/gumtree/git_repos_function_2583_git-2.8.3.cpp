static struct ref *parse_git_refs(struct discovery *heads, int for_push)
{
	struct ref *list = NULL;
	get_remote_heads(-1, heads->buf, heads->len, &list,
			 for_push ? REF_NORMAL : 0, NULL, &heads->shallow);
	return list;
}