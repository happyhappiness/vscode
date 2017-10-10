 			pollsize++;
 		}
 
 		if (!pollsize)
 			break;
 
-		ret = poll(pfd, pollsize, 1000 * keepalive);
+		ret = poll(pfd, pollsize,
+			keepalive < 0 ? -1 : 1000 * keepalive);
+
 		if (ret < 0) {
 			if (errno != EINTR) {
 				error("poll failed, resuming: %s",
 				      strerror(errno));
 				sleep(1);
 			}
