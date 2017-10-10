 	return (git_proxy_command && *git_proxy_command);
 }
 
 static struct child_process *git_proxy_connect(int fd[2], char *host)
 {
 	const char *port = STR(DEFAULT_GIT_PORT);
-	const char **argv;
 	struct child_process *proxy;
 
 	get_host_and_port(&host, &port);
 
-	argv = xmalloc(sizeof(*argv) * 4);
-	argv[0] = git_proxy_command;
-	argv[1] = host;
-	argv[2] = port;
-	argv[3] = NULL;
 	proxy = xcalloc(1, sizeof(*proxy));
-	proxy->argv = argv;
+	argv_array_push(&proxy->args, git_proxy_command);
+	argv_array_push(&proxy->args, host);
+	argv_array_push(&proxy->args, port);
 	proxy->in = -1;
 	proxy->out = -1;
 	if (start_command(proxy))
-		die("cannot start proxy %s", argv[0]);
+		die("cannot start proxy %s", git_proxy_command);
 	fd[0] = proxy->out; /* read from proxy stdout */
 	fd[1] = proxy->in;  /* write to proxy stdin */
 	return proxy;
 }
 
 static const char *get_port_numeric(const char *p)
