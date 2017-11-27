static void *open_connection (void *arg)
{
	struct sockaddr_un addr;

	char *path  = (NULL == sock_file) ? SOCK_PATH : sock_file;
	char *group = (NULL == sock_group) ? COLLECTD_GRP_NAME : sock_group;

	/* create UNIX socket */
	errno = 0;
	if (-1 == (connector_socket = socket (PF_UNIX, SOCK_STREAM, 0))) {
		char errbuf[1024];
		disabled = 1;
		log_err ("socket() failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		pthread_exit ((void *)1);
	}

	addr.sun_family = AF_UNIX;
	sstrncpy (addr.sun_path, path, (size_t)(UNIX_PATH_MAX - 1));

	errno = 0;
	if (-1 == bind (connector_socket, (struct sockaddr *)&addr,
				offsetof (struct sockaddr_un, sun_path)
					+ strlen(addr.sun_path))) {
		char errbuf[1024];
		disabled = 1;
		close (connector_socket);
		connector_socket = -1;
		log_err ("bind() failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		pthread_exit ((void *)1);
	}

	errno = 0;
	if (-1 == listen (connector_socket, 5)) {
		char errbuf[1024];
		disabled = 1;
		close (connector_socket);
		connector_socket = -1;
		log_err ("listen() failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		pthread_exit ((void *)1);
	}

	{
		struct group sg;
		struct group *grp;
		char grbuf[2048];
		int status;

		grp = NULL;
		status = getgrnam_r (group, &sg, grbuf, sizeof (grbuf), &grp);
		if (status != 0)
		{
			char errbuf[1024];
			log_warn ("getgrnam_r (%s) failed: %s", group,
					sstrerror (errno, errbuf, sizeof (errbuf)));
		}
		else if (grp == NULL)
		{
			log_warn ("No such group: `%s'", group);
		}
		else
		{
			status = chown (path, (uid_t) -1, grp->gr_gid);
			if (status != 0)
			{
				char errbuf[1024];
				log_warn ("chown (%s, -1, %i) failed: %s",
						path, (int) grp->gr_gid,
						sstrerror (errno, errbuf, sizeof (errbuf)));
			}
		}
	}

	errno = 0;
	if (0 != chmod (path, sock_perms)) {
		char errbuf[1024];
		log_warn ("chmod() failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
	}

	{ /* initialize collector threads */
		int i   = 0;
		int err = 0;

		pthread_attr_t ptattr;

		conns.head = NULL;
		conns.tail = NULL;

		pthread_attr_init (&ptattr);
		pthread_attr_setdetachstate (&ptattr, PTHREAD_CREATE_DETACHED);

		available_collectors = max_conns;

		collectors =
			(collector_t **)smalloc (max_conns * sizeof (collector_t *));

		for (i = 0; i < max_conns; ++i) {
			collectors[i] = (collector_t *)smalloc (sizeof (collector_t));
			collectors[i]->socket = NULL;

			if (0 != (err = pthread_create (&collectors[i]->thread, &ptattr,
							collect, collectors[i]))) {
				char errbuf[1024];
				log_err ("pthread_create() failed: %s",
						sstrerror (errno, errbuf, sizeof (errbuf)));
				collectors[i]->thread = (pthread_t) 0;
			}
		}

		pthread_attr_destroy (&ptattr);
	}

	while (1) {
		int remote = 0;

		conn_t *connection;

		pthread_mutex_lock (&available_mutex);

		while (0 == available_collectors) {
			pthread_cond_wait (&collector_available, &available_mutex);
		}

		--available_collectors;

		pthread_mutex_unlock (&available_mutex);

		do {
			errno = 0;
			if (-1 == (remote = accept (connector_socket, NULL, NULL))) {
				if (EINTR != errno) {
					char errbuf[1024];
					disabled = 1;
					close (connector_socket);
					connector_socket = -1;
					log_err ("accept() failed: %s",
							sstrerror (errno, errbuf, sizeof (errbuf)));
					pthread_exit ((void *)1);
				}
			}
		} while (EINTR == errno);

		connection = (conn_t *)smalloc (sizeof (conn_t));

		connection->socket = fdopen (remote, "r");
		connection->next   = NULL;

		if (NULL == connection->socket) {
			close (remote);
			continue;
		}

		pthread_mutex_lock (&conns_mutex);

		if (NULL == conns.head) {
			conns.head = connection;
			conns.tail = connection;
		}
		else {
			conns.tail->next = connection;
			conns.tail = conns.tail->next;
		}

		pthread_mutex_unlock (&conns_mutex);

		pthread_cond_signal (&conn_available);
	}
	pthread_exit ((void *)0);
}