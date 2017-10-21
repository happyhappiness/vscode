 	for (i=0;i<3;i++) {
 		close(i); 
 		open("/dev/null", O_RDWR);
 	}
 }
 
-/*******************************************************************
- return the IP addr of the client as a string 
- ******************************************************************/
+/**
+ * Return the IP addr of the client as a string 
+ **/
 char *client_addr(int fd)
 {
-	struct sockaddr sa;
-	struct sockaddr_in *sockin = (struct sockaddr_in *) (&sa);
-	int     length = sizeof(sa);
+	struct sockaddr ss;
+	int     length = sizeof(ss);
 	static char addr_buf[100];
 	static int initialised;
 
 	if (initialised) return addr_buf;
 
 	initialised = 1;
 
-	if (getpeername(fd, &sa, &length)) {
+	if (getpeername(fd, &ss, &length)) {
 		exit_cleanup(RERR_SOCKETIO);
 	}
-	
-	strlcpy(addr_buf,(char *)inet_ntoa(sockin->sin_addr), sizeof(addr_buf));
+
+	getnameinfo(&ss, length,
+		addr_buf, sizeof(addr_buf), NULL, 0, NI_NUMERICHOST);
 	return addr_buf;
 }
 
 
-/*******************************************************************
- return the DNS name of the client 
- ******************************************************************/
+/**
+ * Return the DNS name of the client 
+ **/
 char *client_name(int fd)
 {
-	struct sockaddr sa;
-	struct sockaddr_in *sockin = (struct sockaddr_in *) (&sa);
-	int     length = sizeof(sa);
+	struct sockaddr ss;
+	int     length = sizeof(ss);
 	static char name_buf[100];
-	struct hostent *hp;
-	char **p;
+	static char port_buf[100];
 	char *def = "UNKNOWN";
 	static int initialised;
+	struct addrinfo hints, *res, *res0;
+	int error;
 
 	if (initialised) return name_buf;
 
 	initialised = 1;
 
 	strcpy(name_buf,def);
 
-	if (getpeername(fd, &sa, &length)) {
+	if (getpeername(fd, (struct sockaddr *)&ss, &length)) {
+		/* FIXME: Can we really not continue? */
+		rprintf(FERROR, RSYNC_NAME ": getpeername on fd%d failed: %s\n",
+			fd, strerror(errno));
 		exit_cleanup(RERR_SOCKETIO);
 	}
 
-	/* Look up the remote host name. */
-	if ((hp = gethostbyaddr((char *) &sockin->sin_addr,
-				sizeof(sockin->sin_addr),
-				AF_INET))) {
-		strlcpy(name_buf,(char *)hp->h_name,sizeof(name_buf));
+#ifdef INET6
+        if (ss.sa_family == AF_INET6 && 
+	    IN6_IS_ADDR_V4MAPPED(&((struct sockaddr_in6 *)&ss)->sin6_addr)) {
+		struct sockaddr_in6 sin6;
+		struct sockaddr_in *sin;
+
+		memcpy(&sin6, &ss, sizeof(sin6));
+		sin = (struct sockaddr_in *)&ss;
+		memset(sin, 0, sizeof(*sin));
+		sin->sin_family = AF_INET;
+		length = sizeof(struct sockaddr_in);
+#ifdef HAVE_SOCKADDR_LEN
+		sin->sin_len = length;
+#endif
+		sin->sin_port = sin6.sin6_port;
+		memcpy(&sin->sin_addr, &sin6.sin6_addr.s6_addr[12],
+			sizeof(sin->sin_addr));
+        }
+#endif
+
+	/* reverse lookup */
+	if (getnameinfo((struct sockaddr *)&ss, length,
+			name_buf, sizeof(name_buf), port_buf, sizeof(port_buf),
+			NI_NAMEREQD | NI_NUMERICSERV) != 0) {
+		strcpy(name_buf, def);
+		rprintf(FERROR, "reverse name lookup failed\n");
+	}
+
+	/* forward lookup */
+	memset(&hints, 0, sizeof(hints));
+	hints.ai_family = PF_UNSPEC;
+	hints.ai_flags = AI_CANONNAME;
+	hints.ai_socktype = SOCK_STREAM;
+	error = getaddrinfo(name_buf, port_buf, &hints, &res0);
+	if (error) {
+		strcpy(name_buf, def);
+		rprintf(FERROR,
+			RSYNC_NAME ": forward name lookup for %s failed: %s\n",
+			port_buf,
+			gai_strerror(error));
+		return name_buf;
+	}
+
+	/* XXX sin6_flowinfo and other fields */
+	for (res = res0; res; res = res->ai_next) {
+		if (res->ai_family != ss.sa_family)
+			continue;
+		if (res->ai_addrlen != length)
+			continue;
+		if (memcmp(res->ai_addr, &ss, res->ai_addrlen) == 0)
+			break;
 	}
 
+	/* TODO: Do a  forward lookup as well to prevent spoofing */
 
-	/* do a forward lookup as well to prevent spoofing */
-	hp = gethostbyname(name_buf);
-	if (!hp) {
-		strcpy(name_buf,def);
-		rprintf(FERROR,"reverse name lookup failed\n");
-	} else {
-		for (p=hp->h_addr_list;*p;p++) {
-			if (memcmp(*p, &sockin->sin_addr, hp->h_length) == 0) {
-				break;
-			}
-		}
-		if (!*p) {
-			strcpy(name_buf,def);
-			rprintf(FERROR,"reverse name lookup mismatch - spoofed address?\n");
-		} 
+	if (res == NULL) {
+		strcpy(name_buf, def);
+		rprintf(FERROR, RSYNC_NAME ": "
+			"reverse name lookup mismatch on fd%d - spoofed address?\n",
+			fd);
 	}
 
+	freeaddrinfo(res0);
 	return name_buf;
 }
 
+
 /*******************************************************************
-convert a string to an IP address. The string can be a name or
-dotted decimal number
-  ******************************************************************/
-struct in_addr *ip_address(const char *str)
+this is like socketpair but uses tcp. It is used by the Samba
+regression test code
+The function guarantees that nobody else can attach to the socket,
+or if they do that this function fails and the socket gets closed
+returns 0 on success, -1 on failure
+the resulting file descriptors are symmetrical
+ ******************************************************************/
+static int socketpair_tcp(int fd[2])
 {
-	static struct in_addr ret;
-	struct hostent *hp;
+	int listener;
+	struct sockaddr_in sock;
+	struct sockaddr_in sock2;
+	socklen_t socklen = sizeof(sock);
+	int connect_done = 0;
+	
+	fd[0] = fd[1] = listener = -1;
 
-	/* try as an IP address */
-	if (inet_aton(str, &ret) != 0) {
-		return &ret;
-	}
+	memset(&sock, 0, sizeof(sock));
+	
+	if ((listener = socket(PF_INET, SOCK_STREAM, 0)) == -1) goto failed;
 
-	/* otherwise assume it's a network name of some sort and use 
-	   gethostbyname */
-	if ((hp = gethostbyname(str)) == 0) {
-		rprintf(FERROR, "gethostbyname: Unknown host. %s\n",str);
-		return NULL;
-	}
+        memset(&sock2, 0, sizeof(sock2));
+#ifdef HAVE_SOCK_SIN_LEN
+        sock2.sin_len = sizeof(sock2);
+#endif
+        sock2.sin_family = PF_INET;
+
+        bind(listener, (struct sockaddr *)&sock2, sizeof(sock2));
+
+	if (listen(listener, 1) != 0) goto failed;
+
+	if (getsockname(listener, (struct sockaddr *)&sock, &socklen) != 0) goto failed;
+
+	if ((fd[1] = socket(PF_INET, SOCK_STREAM, 0)) == -1) goto failed;
+
+	set_nonblocking(fd[1]);
 
-	if (hp->h_addr == NULL) {
-		rprintf(FERROR, "gethostbyname: host address is invalid for host %s\n",str);
-		return NULL;
+	sock.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
+
+	if (connect(fd[1],(struct sockaddr *)&sock,sizeof(sock)) == -1) {
+		if (errno != EINPROGRESS) goto failed;
+	} else {
+		connect_done = 1;
 	}
 
-	if (hp->h_length > sizeof(ret)) {
-		rprintf(FERROR, "gethostbyname: host address is too large\n");
-		return NULL;
+	if ((fd[0] = accept(listener, (struct sockaddr *)&sock, &socklen)) == -1) goto failed;
+
+	close(listener);
+	if (connect_done == 0) {
+		if (connect(fd[1],(struct sockaddr *)&sock,sizeof(sock)) != 0
+		    && errno != EISCONN) goto failed;
 	}
 
-	memcpy(&ret.s_addr, hp->h_addr, hp->h_length);
+	set_blocking (fd[1]);
 
-	return(&ret);
+	/* all OK! */
+	return 0;
+
+ failed:
+	if (fd[0] != -1) close(fd[0]);
+	if (fd[1] != -1) close(fd[1]);
+	if (listener != -1) close(listener);
+	return -1;
 }
+
+
+/*******************************************************************
+run a program on a local tcp socket, this is used to launch smbd
+when regression testing
+the return value is a socket which is attached to a subprocess
+running "prog". stdin and stdout are attached. stderr is left
+attached to the original stderr
+ ******************************************************************/
+int sock_exec(const char *prog)
+{
+	int fd[2];
+	if (socketpair_tcp(fd) != 0) {
+		rprintf (FERROR, RSYNC_NAME
+			 ": socketpair_tcp failed (%s)\n",
+			 strerror(errno));
+		return -1;
+	}
+	if (fork() == 0) {
+		close(fd[0]);
+		close(0);
+		close(1);
+		dup(fd[1]);
+		dup(fd[1]);
+		if (verbose > 3)
+			fprintf (stderr,
+				 RSYNC_NAME ": execute socket program \"%s\"\n",
+				 prog);
+		exit (system (prog));
+	}
+	close (fd[1]);
+	return fd[0];
+}
+
+
+
