static void *collect (void *arg)
{
	collector_t *this = (collector_t *)arg;

	char *buffer = (char *)smalloc (BUFSIZE);

	while (1) {
		int loop = 1;

		conn_t *connection;

		pthread_mutex_lock (&conns_mutex);

		while (NULL == conns.head) {
			pthread_cond_wait (&conn_available, &conns_mutex);
		}

		connection = conns.head;
		conns.head = conns.head->next;

		if (NULL == conns.head) {
			conns.tail = NULL;
		}

		this->socket = connection->socket;

		pthread_mutex_unlock (&conns_mutex);

		connection->buffer = buffer;
		connection->idx    = 0;
		connection->length = 0;

		{ /* put the socket in non-blocking mode */
			int flags = 0;

			errno = 0;
			if (-1 == fcntl (connection->socket, F_GETFL, &flags)) {
				char errbuf[1024];
				log_err ("fcntl() failed: %s",
						sstrerror (errno, errbuf, sizeof (errbuf)));
				loop = 0;
			}

			errno = 0;
			if (-1 == fcntl (connection->socket, F_SETFL, flags | O_NONBLOCK)) {
				char errbuf[1024];
				log_err ("fcntl() failed: %s",
						sstrerror (errno, errbuf, sizeof (errbuf)));
				loop = 0;
			}
		}

		while (loop) {
			char *line = read_line (connection);

			if (NULL == line) {
				loop = 0;
				break;
			}

			if (':' != line[1]) {
				log_err ("syntax error in line '%s'", line);
				continue;
			}

			if ('e' == line[0]) { /* e:<type>:<bytes> */
				char *ptr  = NULL;
				char *type = strtok_r (line + 2, ":", &ptr);
				char *tmp  = strtok_r (NULL, ":", &ptr);
				int  bytes = 0;

				if (NULL == tmp) {
					log_err ("syntax error in line '%s'", line);
					continue;
				}

				bytes = atoi (tmp);

				pthread_mutex_lock (&count_mutex);
				type_list_incr (&count, type, 1);
				pthread_mutex_unlock (&count_mutex);

				if (bytes > 0) {
					pthread_mutex_lock (&size_mutex);
					type_list_incr (&size, type, bytes);
					pthread_mutex_unlock (&size_mutex);
				}
			}
			else if ('s' == line[0]) { /* s:<value> */
				pthread_mutex_lock (&score_mutex);
				score = (score * (double)score_count + atof (line + 2))
						/ (double)(score_count + 1);
				++score_count;
				pthread_mutex_unlock (&score_mutex);
			}
			else if ('c' == line[0]) { /* c:<type1>[,<type2>,...] */
				char *ptr  = NULL;
				char *type = strtok_r (line + 2, ",", &ptr);

				do {
					pthread_mutex_lock (&check_mutex);
					type_list_incr (&check, type, 1);
					pthread_mutex_unlock (&check_mutex);
				} while (NULL != (type = strtok_r (NULL, ",", &ptr)));
			}
			else {
				log_err ("unknown type '%c'", line[0]);
			}
		} /* while (loop) */

		close (connection->socket);
		free (connection);

		this->socket = -1;

		pthread_mutex_lock (&available_mutex);
		++available_collectors;
		pthread_mutex_unlock (&available_mutex);

		pthread_cond_signal (&collector_available);
	} /* while (1) */

	free (buffer);
	pthread_exit ((void *)0);
}