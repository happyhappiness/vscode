static void msg_list_add(int code, char *buf, int len)
{
	struct msg_list *ml;

	if (!(ml = new(struct msg_list)))
		exit_cleanup(RERR_MALLOC);
	ml->next = NULL;
	if (!(ml->buf = new_array(char, len+4)))
		exit_cleanup(RERR_MALLOC);
	SIVAL(ml->buf, 0, ((code+MPLEX_BASE)<<24) | len);
	memcpy(ml->buf+4, buf, len);
	ml->len = len+4;
	if (msg_list_tail)
		msg_list_tail->next = ml;
	else
		msg_list_head = ml;
	msg_list_tail = ml;
}