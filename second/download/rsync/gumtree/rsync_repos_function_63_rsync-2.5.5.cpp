static void whine_about_eof (void)
{
	/**
	   It's almost always an error to get an EOF when we're trying
	   to read from the network, because the protocol is
	   self-terminating.
	   
	   However, there is one unfortunate cases where it is not,
	   which is rsync <2.4.6 sending a list of modules on a
	   server, since the list is terminated by closing the socket.
	   So, for the section of the program where that is a problem
	   (start_socket_client), kludge_around_eof is True and we
	   just exit.
	*/

	if (kludge_around_eof)
		exit_cleanup (0);
	else {
		rprintf (FERROR,
			 "%s: connection unexpectedly closed "
			 "(%.0f bytes read so far)\n",
			 RSYNC_NAME, (double)stats.total_read);
	
		exit_cleanup (RERR_STREAMIO);
	}
}