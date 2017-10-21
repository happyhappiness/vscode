 		}
 #endif
 
 		/* Now we've got a socket - we need to bind it. */
 		if (bind(s, resp->ai_addr, resp->ai_addrlen) < 0) {
 			/* Nope, try another */
+			int r = asprintf(&errmsgs[ecnt++],
+				"bind() failed: %s (address-family %d)\n",
+				strerror(errno), (int)resp->ai_family);
+			if (r < 0)
+				out_of_memory("open_socket_in");
 			close(s);
 			continue;
 		}
 
 		socks[i++] = s;
 	}
 	socks[i] = -1;
 
 	if (all_ai)
 		freeaddrinfo(all_ai);
 
+	/* Only output the socket()/bind() messages if we were totally
+	 * unsuccessful, or if the daemon is being run with -vv. */
+	for (s = 0; s < ecnt; s++) {
+		if (!i || verbose > 1)
+			rwrite(FLOG, errmsgs[s], strlen(errmsgs[s]));
+		free(errmsgs[s]);
+	}
+	free(errmsgs);
+
 	if (!i) {
 		rprintf(FERROR,
 			"unable to bind any inbound sockets on port %d\n",
 			port);
 		free(socks);
 		return NULL;
