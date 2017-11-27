static int email_shutdown (void)
{
	int i = 0;

	if (connector != ((pthread_t) 0)) {
		pthread_kill (connector, SIGTERM);
		connector = (pthread_t) 0;
	}

	if (connector_socket >= 0) {
		close (connector_socket);
		connector_socket = -1;
	}

	/* don't allow any more connections to be processed */
	pthread_mutex_lock (&conns_mutex);

	if (collectors != NULL) {
		for (i = 0; i < max_conns; ++i) {
			if (collectors[i] == NULL)
				continue;

			if (collectors[i]->thread != ((pthread_t) 0)) {
				pthread_kill (collectors[i]->thread, SIGTERM);
				collectors[i]->thread = (pthread_t) 0;
			}

			if (collectors[i]->socket >= 0) {
				close (collectors[i]->socket);
				collectors[i]->socket = -1;
			}
		}
	} /* if (collectors != NULL) */

	pthread_mutex_unlock (&conns_mutex);

	unlink (sock_file);
	errno = 0;

	return (0);
}