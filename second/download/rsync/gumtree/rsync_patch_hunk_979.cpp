 		select_timeout = allowed_lull;
 
 	if (read_batch)
 		allowed_lull = 0;
 }
 
-/* Setup the fd used to receive MSG_* messages.  Only needed during the
- * early stages of being a local sender (up through the sending of the
- * file list) or when we're the generator (to fetch the messages from
- * the receiver). */
-void set_msg_fd_in(int fd)
-{
-	msg_fd_in = fd;
-}
-
-/* Setup the fd used to send our MSG_* messages.  Only needed when
- * we're the receiver (to send our messages to the generator). */
-void set_msg_fd_out(int fd)
-{
-	msg_fd_out = fd;
-	set_nonblocking(msg_fd_out);
-}
-
-/* Add a message to the pending MSG_* list. */
-static void msg_list_add(struct msg_list *lst, int code, const char *buf, int len, int convert)
-{
-	struct msg_list_item *m;
-	int sz = len + 4 + sizeof m[0] - 1;
-
-	if (!(m = (struct msg_list_item *)new_array(char, sz)))
-		out_of_memory("msg_list_add");
-	m->next = NULL;
-	m->convert = convert;
-	SIVAL(m->buf, 0, ((code+MPLEX_BASE)<<24) | len);
-	memcpy(m->buf + 4, buf, len);
-	if (lst->tail)
-		lst->tail->next = m;
-	else
-		lst->head = m;
-	lst->tail = m;
-}
-
-static inline int flush_a_msg(int fd)
-{
-	struct msg_list_item *m = msg_queue.head;
-	int len = IVAL(m->buf, 0) & 0xFFFFFF;
-	int tag = *((uchar*)m->buf+3) - MPLEX_BASE;
-
-	if (!(msg_queue.head = m->next))
-		msg_queue.tail = NULL;
-
-	defer_forwarding_messages++;
-	mplex_write(fd, tag, m->buf + 4, len, m->convert);
-	defer_forwarding_messages--;
-
-	free(m);
-
-	return len;
-}
-
-static void msg_flush(void)
-{
-	if (am_generator) {
-		while (msg_queue.head && io_multiplexing_out)
-			stats.total_written += flush_a_msg(sock_f_out) + 4;
-	} else {
-		while (msg_queue.head)
-			(void)flush_a_msg(msg_fd_out);
-	}
-}
-
 static void check_for_d_option_error(const char *msg)
 {
 	static char rsync263_opts[] = "BCDHIKLPRSTWabceghlnopqrtuvxz";
 	char *colon;
 	int saw_d = 0;
 
