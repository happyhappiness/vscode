 	for (;;) {
 		struct ref *ref;
 		unsigned char old_sha1[20];
 		char *name;
 		int len, name_len;
 		char *buffer = packet_buffer;
+		const char *arg;
 
 		len = packet_read(in, &src_buf, &src_len,
 				  packet_buffer, sizeof(packet_buffer),
 				  PACKET_READ_GENTLE_ON_EOF |
 				  PACKET_READ_CHOMP_NEWLINE);
 		if (len < 0)
 			die_initial_contact(got_at_least_one_head);
 
 		if (!len)
 			break;
 
-		if (len > 4 && starts_with(buffer, "ERR "))
-			die("remote error: %s", buffer + 4);
+		if (len > 4 && skip_prefix(buffer, "ERR ", &arg))
+			die("remote error: %s", arg);
 
-		if (len == 48 && starts_with(buffer, "shallow ")) {
-			if (get_sha1_hex(buffer + 8, old_sha1))
-				die("protocol error: expected shallow sha-1, got '%s'", buffer + 8);
+		if (len == 48 && skip_prefix(buffer, "shallow ", &arg)) {
+			if (get_sha1_hex(arg, old_sha1))
+				die("protocol error: expected shallow sha-1, got '%s'", arg);
 			if (!shallow_points)
 				die("repository on the other end cannot be shallow");
 			sha1_array_append(shallow_points, old_sha1);
 			continue;
 		}
 
