 
 		ret = poll(pfd, pollsize,
 			keepalive < 0 ? -1 : 1000 * keepalive);
 
 		if (ret < 0) {
 			if (errno != EINTR) {
-				error("poll failed, resuming: %s",
-				      strerror(errno));
+				error_errno("poll failed, resuming");
 				sleep(1);
 			}
 			continue;
 		}
 		if (0 <= pe && (pfd[pe].revents & (POLLIN|POLLHUP))) {
 			/* Status ready; we ship that in the side-band
