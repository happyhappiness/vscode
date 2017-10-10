 	ACK_common,
 	ACK_ready
 };
 
 static void consume_shallow_list(struct fetch_pack_args *args, int fd)
 {
-	if (args->stateless_rpc && args->depth > 0) {
+	if (args->stateless_rpc && args->deepen) {
 		/* If we sent a depth we will get back "duplicate"
 		 * shallow and unshallow commands every time there
 		 * is a block of have lines exchanged.
 		 */
 		char *line;
 		while ((line = packet_read_line(fd, NULL))) {
 			if (starts_with(line, "shallow "))
 				continue;
 			if (starts_with(line, "unshallow "))
 				continue;
-			die("git fetch-pack: expected shallow list");
+			die(_("git fetch-pack: expected shallow list"));
 		}
 	}
 }
 
 static enum ack_type get_ack(int fd, unsigned char *result_sha1)
 {
 	int len;
 	char *line = packet_read_line(fd, &len);
 	const char *arg;
 
 	if (!len)
-		die("git fetch-pack: expected ACK/NAK, got EOF");
+		die(_("git fetch-pack: expected ACK/NAK, got EOF"));
 	if (!strcmp(line, "NAK"))
 		return NAK;
 	if (skip_prefix(line, "ACK ", &arg)) {
 		if (!get_sha1_hex(arg, result_sha1)) {
 			arg += 40;
 			len -= arg - line;
