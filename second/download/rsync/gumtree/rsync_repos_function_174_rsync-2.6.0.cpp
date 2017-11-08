static void err_list_add(int code, char *buf, int len)
{
	struct err_list *el;
	el = new(struct err_list);
	if (!el) exit_cleanup(RERR_MALLOC);
	el->next = NULL;
	el->buf = new_array(char, len+4);
	if (!el->buf) exit_cleanup(RERR_MALLOC);
	memcpy(el->buf+4, buf, len);
	SIVAL(el->buf, 0, ((code+MPLEX_BASE)<<24) | len);
	el->len = len+4;
	el->written = 0;
	if (err_list_tail) {
		err_list_tail->next = el;
	} else {
		err_list_head = el;
	}
	err_list_tail = el;
}