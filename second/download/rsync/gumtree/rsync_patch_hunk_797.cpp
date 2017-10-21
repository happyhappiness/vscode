 			break;
 		}
 
 		read_loop(fd, line, 4);
 		tag = IVAL(line, 0);
 
-		remaining = tag & 0xFFFFFF;
+		msg_bytes = tag & 0xFFFFFF;
 		tag = (tag >> 24) - MPLEX_BASE;
 
 		switch (tag) {
 		case MSG_DATA:
-			if (remaining > iobuf_in_siz) {
+			if (msg_bytes > iobuf_in_siz) {
 				if (!(iobuf_in = realloc_array(iobuf_in, char,
-							       remaining)))
+							       msg_bytes)))
 					out_of_memory("readfd_unbuffered");
-				iobuf_in_siz = remaining;
+				iobuf_in_siz = msg_bytes;
 			}
-			read_loop(fd, iobuf_in, remaining);
+			read_loop(fd, iobuf_in, msg_bytes);
+			remaining = msg_bytes;
 			iobuf_in_ndx = 0;
 			break;
 		case MSG_DELETED:
-			if (remaining >= sizeof line) {
-				rprintf(FERROR, "invalid multi-message %d:%ld\n",
-					tag, (long)remaining);
-				exit_cleanup(RERR_STREAMIO);
-			}
-			read_loop(fd, line, remaining);
-			line[remaining] = '\0';
+			if (msg_bytes >= sizeof line)
+				goto overflow;
+			read_loop(fd, line, msg_bytes);
+			line[msg_bytes] = '\0';
 			/* A directory name was sent with the trailing null */
-			if (remaining > 0 && !line[remaining-1])
+			if (msg_bytes > 0 && !line[msg_bytes-1])
 				log_delete(line, S_IFDIR);
 			else
 				log_delete(line, S_IFREG);
-			remaining = 0;
 			break;
 		case MSG_SUCCESS:
-			if (remaining != 4) {
+			if (msg_bytes != 4) {
 				rprintf(FERROR, "invalid multi-message %d:%ld [%s]\n",
-					tag, (long)remaining, who_am_i());
+					tag, (long)msg_bytes, who_am_i());
 				exit_cleanup(RERR_STREAMIO);
 			}
-			read_loop(fd, line, remaining);
+			read_loop(fd, line, msg_bytes);
 			successful_send(IVAL(line, 0));
-			remaining = 0;
 			break;
 		case MSG_INFO:
 		case MSG_ERROR:
-			if (remaining >= sizeof line) {
+			if (msg_bytes >= sizeof line) {
+			    overflow:
 				rprintf(FERROR,
 					"multiplexing overflow %d:%ld [%s]\n",
-					tag, (long)remaining, who_am_i());
+					tag, (long)msg_bytes, who_am_i());
 				exit_cleanup(RERR_STREAMIO);
 			}
-			read_loop(fd, line, remaining);
-			rwrite((enum logcode)tag, line, remaining);
-			remaining = 0;
+			read_loop(fd, line, msg_bytes);
+			rwrite((enum logcode)tag, line, msg_bytes);
 			break;
 		default:
 			rprintf(FERROR, "unexpected tag %d [%s]\n",
 				tag, who_am_i());
 			exit_cleanup(RERR_STREAMIO);
 		}
