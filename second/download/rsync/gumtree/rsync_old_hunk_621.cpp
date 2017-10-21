/* -*- c-file-style: "linux"; -*-
   
   Copyright (C) 1998-2001 by Andrew Tridgell <tridge@samba.org>
   Copyright (C) 2001-2002 by Martin Pool <mbp@samba.org>
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/* the socket based protocol for setting up a connection with rsyncd */

#include "rsync.h"

extern int module_id;
extern int read_only;
extern int verbose;
extern int rsync_port;
char *auth_user;
int sanitize_paths = 0;

/**
 * Run a client connected to an rsyncd.  The alternative to this
 * function for remote-shell connections is do_cmd().
 *
 * After initial server startup, hands over to client_run().
 *
 * @return -1 for error in startup, or the result of client_run().
 **/
int start_socket_client(char *host, char *path, int argc, char *argv[])
{
	int fd, i;
	char *sargs[MAX_ARGS];
	int sargc=0;
	char line[MAXPATHLEN];
	char *p, *user=NULL;
	extern int remote_version;
	extern int am_sender;
	extern char *shell_cmd;
	extern int list_only;
	extern int kludge_around_eof;
	extern char *bind_address;
	extern int default_af_hint;
       
	if (argc == 0 && !am_sender) {
		extern int list_only;
		list_only = 1;
	}

        /* This is just a friendliness enhancement: if the connection
         * is to an rsyncd then there is no point specifying the -e option.
         * Note that this is only set if the -e was explicitly specified,
         * not if the environment variable just happens to be set.
         * See http://lists.samba.org/pipermail/rsync/2000-September/002744.html
         */
        if (shell_cmd) {
                rprintf(FERROR, "WARNING: --rsh or -e option ignored when "
                        "connecting to rsync daemon\n");
                /* continue */
        }
        
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

	if (!user) user = getenv("USER");
	if (!user) user = getenv("LOGNAME");

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
	
	server_options(sargs,&sargc);

	sargs[sargc++] = ".";

	if (path && *path) 
		sargs[sargc++] = path;

	sargs[sargc] = NULL;

	io_printf(fd,"@RSYNCD: %d\n", PROTOCOL_VERSION);

	if (!read_line(fd, line, sizeof(line)-1)) {
		rprintf(FERROR, "rsync: did not see server greeting\n");
		return -1;
	}

	if (sscanf(line,"@RSYNCD: %d", &remote_version) != 1) {
		/* note that read_line strips of \n or \r */
