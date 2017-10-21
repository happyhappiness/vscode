static void msg_list_add(struct msg_list *lst, int code, const char *buf, int len, int convert)
{
	struct msg_list_item *m;
	int sz = len + 4 + sizeof m[0] - 1;

	if (!(m = (struct msg_list_item *)new_array(char, sz)))
		out_of_memory("msg_list_add");
	m->next = NULL;
	m->convert = convert;
	SIVAL(m->buf, 0, ((code+MPLEX_BASE)<<24) | len);
	memcpy(m->buf + 4, buf, len);
	if (lst->tail)
		lst->tail->next = m;
	else
		lst->head = m;
	lst->tail = m;
}