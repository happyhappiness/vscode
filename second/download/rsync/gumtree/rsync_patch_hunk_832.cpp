 {
 	msg_fd_out = fd;
 	set_nonblocking(msg_fd_out);
 }
 
 /* Add a message to the pending MSG_* list. */
-static void msg_list_add(int code, char *buf, int len)
+static void msg_list_add(struct msg_list *lst, int code, char *buf, int len)
 {
-	struct msg_list_item *ml;
+	struct msg_list_item *m;
+	int sz = len + 4 + sizeof m[0] - 1;
 
-	if (!(ml = new(struct msg_list_item)))
+	if (!(m = (struct msg_list_item *)new_array(char, sz)))
 		out_of_memory("msg_list_add");
-	ml->next = NULL;
-	if (!(ml->buf = new_array(char, len+4)))
-		out_of_memory("msg_list_add");
-	SIVAL(ml->buf, 0, ((code+MPLEX_BASE)<<24) | len);
-	memcpy(ml->buf+4, buf, len);
-	ml->len = len+4;
-	if (msg_list.tail)
-		msg_list.tail->next = ml;
+	m->next = NULL;
+	m->len = len + 4;
+	SIVAL(m->buf, 0, ((code+MPLEX_BASE)<<24) | len);
+	memcpy(m->buf + 4, buf, len);
+	if (lst->tail)
+		lst->tail->next = m;
 	else
-		msg_list.head = ml;
-	msg_list.tail = ml;
+		lst->head = m;
+	lst->tail = m;
 }
 
 /* Read a message from the MSG_* fd and handle it.  This is called either
  * during the early stages of being a local sender (up through the sending
  * of the file list) or when we're the generator (to fetch the messages
  * from the receiver). */
