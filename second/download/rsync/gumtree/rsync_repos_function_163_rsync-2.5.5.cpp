void err_list_push(void)
{
	if (log_error_fd == -1) return;

	while (err_list_head) {
		struct err_list *el = err_list_head;
		int n = write(log_error_fd, el->buf+el->written, el->len - el->written);
		/* don't check for an error if the best way of handling the error is
		   to ignore it */
		if (n == -1) break;
		if (n > 0) {
			el->written += n;
		}
		if (el->written == el->len) {
			free(el->buf);
			err_list_head = el->next;
			if (!err_list_head) err_list_tail = NULL;
			free(el);
		}
	}
}