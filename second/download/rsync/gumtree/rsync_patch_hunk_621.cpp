 /* -*- c-file-style: "linux"; -*-
-   
-   Copyright (C) 1998-2001 by Andrew Tridgell <tridge@samba.org>
-   Copyright (C) 2001-2002 by Martin Pool <mbp@samba.org>
-   
-   This program is free software; you can redistribute it and/or modify
-   it under the terms of the GNU General Public License as published by
-   the Free Software Foundation; either version 2 of the License, or
-   (at your option) any later version.
-   
-   This program is distributed in the hope that it will be useful,
-   but WITHOUT ANY WARRANTY; without even the implied warranty of
-   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-   GNU General Public License for more details.
-   
-   You should have received a copy of the GNU General Public License
-   along with this program; if not, write to the Free Software
-   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
-*/
+ * 
+ * Copyright (C) 1998-2001 by Andrew Tridgell <tridge@samba.org>
+ * Copyright (C) 2001-2002 by Martin Pool <mbp@samba.org>
+ * 
+ * This program is free software; you can redistribute it and/or modify
+ * it under the terms of the GNU General Public License as published by
+ * the Free Software Foundation; either version 2 of the License, or
+ * (at your option) any later version.
+ * 
+ * This program is distributed in the hope that it will be useful,
+ * but WITHOUT ANY WARRANTY; without even the implied warranty of
+ * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+ * GNU General Public License for more details.
+ * 
+ * You should have received a copy of the GNU General Public License
+ * along with this program; if not, write to the Free Software
+ * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
+ */
 
-/* the socket based protocol for setting up a connection with rsyncd */
+/**
+ * @file
+ *
+ * The socket based protocol for setting up a connection with
+ * rsyncd.
+ **/
 
 #include "rsync.h"
 
 extern int module_id;
 extern int read_only;
 extern int verbose;
 extern int rsync_port;
 char *auth_user;
-int sanitize_paths = 0;
+extern int sanitize_paths;
 
 /**
  * Run a client connected to an rsyncd.  The alternative to this
  * function for remote-shell connections is do_cmd().
  *
- * After initial server startup, hands over to client_run().
+ * After negotiating which module to use and reading the server's
+ * motd, this hands over to client_run().  Telling the server the
+ * module will cause it to chroot/setuid/etc.
+ *
+ * Instead of doing a transfer, the client may at this stage instead
+ * get a listing of remote modules and exit.
  *
  * @return -1 for error in startup, or the result of client_run().
+ * Either way, it eventually gets passed to exit_cleanup().
  **/
 int start_socket_client(char *host, char *path, int argc, char *argv[])
 {
-	int fd, i;
-	char *sargs[MAX_ARGS];
-	int sargc=0;
-	char line[MAXPATHLEN];
+	int fd, ret;
 	char *p, *user=NULL;
-	extern int remote_version;
-	extern int am_sender;
-	extern char *shell_cmd;
-	extern int list_only;
-	extern int kludge_around_eof;
 	extern char *bind_address;
 	extern int default_af_hint;
        
-	if (argc == 0 && !am_sender) {
-		extern int list_only;
-		list_only = 1;
-	}
-
-        /* This is just a friendliness enhancement: if the connection
-         * is to an rsyncd then there is no point specifying the -e option.
-         * Note that this is only set if the -e was explicitly specified,
-         * not if the environment variable just happens to be set.
-         * See http://lists.samba.org/pipermail/rsync/2000-September/002744.html
-         */
-        if (shell_cmd) {
-                rprintf(FERROR, "WARNING: --rsh or -e option ignored when "
-                        "connecting to rsync daemon\n");
-                /* continue */
-        }
-        
+	/* this is redundant with code in start_inband_exchange(), but
+	   this short-circuits a problem before we open a socket, and 
+	   the extra check won't hurt */
 	if (*path == '/') {
 		rprintf(FERROR,"ERROR: The remote path must start with a module name not a /\n");
 		return -1;
 	}
 
 	p = strchr(host, '@');
 	if (p) {
 		user = host;
 		host = p+1;
 		*p = 0;
 	}
 
-	if (!user) user = getenv("USER");
-	if (!user) user = getenv("LOGNAME");
-
 	if (verbose >= 2) {
 		/* FIXME: If we're going to use a socket program for
 		 * testing, then this message is wrong.  We need to
 		 * say something like "(except really using %s)" */
 		rprintf(FINFO, "opening tcp connection to %s port %d\n",
 			host, rsync_port);
 	}
 	fd = open_socket_out_wrapped (host, rsync_port, bind_address,
 				      default_af_hint);
 	if (fd == -1) {
 		exit_cleanup(RERR_SOCKETIO);
 	}
-	
-	server_options(sargs,&sargc);
+
+	ret = start_inband_exchange(user, path, fd, fd, argc);
+
+	return ret < 0? ret : client_run(fd, fd, -1, argc, argv);
+}
+
+int start_inband_exchange(char *user, char *path, int f_in, int f_out, int argc)
+{
+	int i;
+	char *sargs[MAX_ARGS];
+	int sargc = 0;
+	char line[MAXPATHLEN];
+	char *p;
+	extern int remote_version;
+	extern int kludge_around_eof;
+	extern int am_sender;
+	extern int daemon_over_rsh;
+	extern int list_only;
+
+	if (argc == 0 && !am_sender)
+		list_only = 1;
+
+	if (*path == '/') {
+		rprintf(FERROR, "ERROR: The remote path must start with a module name\n");
+		return -1;
+	}
+
+	if (!user) user = getenv("USER");
+	if (!user) user = getenv("LOGNAME");
+
+	/* set daemon_over_rsh to false since we need to build the 
+	   true set of args passed through the rsh/ssh connection; 
+	   this is a no-op for direct-socket-connection mode */
+	daemon_over_rsh = 0;
+	server_options(sargs, &sargc);
 
 	sargs[sargc++] = ".";
 
 	if (path && *path) 
 		sargs[sargc++] = path;
 
 	sargs[sargc] = NULL;
 
-	io_printf(fd,"@RSYNCD: %d\n", PROTOCOL_VERSION);
+	io_printf(f_out, "@RSYNCD: %d\n", PROTOCOL_VERSION);
 
-	if (!read_line(fd, line, sizeof(line)-1)) {
+	if (!read_line(f_in, line, sizeof(line)-1)) {
 		rprintf(FERROR, "rsync: did not see server greeting\n");
 		return -1;
 	}
 
 	if (sscanf(line,"@RSYNCD: %d", &remote_version) != 1) {
 		/* note that read_line strips of \n or \r */
