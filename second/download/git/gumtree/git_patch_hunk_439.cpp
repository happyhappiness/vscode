 	 */
 	argv[0] = "upload-archive--writer";
 	writer.out = writer.err = -1;
 	writer.git_cmd = 1;
 	if (start_command(&writer)) {
 		int err = errno;
-		packet_write(1, "NACK unable to spawn subprocess\n");
+		packet_write_fmt(1, "NACK unable to spawn subprocess\n");
 		die("upload-archive: %s", strerror(err));
 	}
 
-	packet_write(1, "ACK\n");
+	packet_write_fmt(1, "ACK\n");
 	packet_flush(1);
 
 	while (1) {
 		struct pollfd pfd[2];
 
 		pfd[0].fd = writer.out;
