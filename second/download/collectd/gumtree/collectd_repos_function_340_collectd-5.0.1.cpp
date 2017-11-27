static int us_open_socket (void)
{
	struct sockaddr_un sa;
	int status;

	sock_fd = socket (PF_UNIX, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		char errbuf[1024];
		ERROR ("unixsock plugin: socket failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	memset (&sa, '\0', sizeof (sa));
	sa.sun_family = AF_UNIX;
	sstrncpy (sa.sun_path, (sock_file != NULL) ? sock_file : US_DEFAULT_PATH,
			sizeof (sa.sun_path));

	DEBUG ("unixsock plugin: socket path = %s", sa.sun_path);

	if (delete_socket)
	{
		errno = 0;
		status = unlink (sa.sun_path);
		if ((status != 0) && (errno != ENOENT))
		{
			char errbuf[1024];
			WARNING ("unixsock plugin: Deleting socket file \"%s\" failed: %s",
					sa.sun_path,
					sstrerror (errno, errbuf, sizeof (errbuf)));
		}
		else if (status == 0)
		{
			INFO ("unixsock plugin: Successfully deleted socket file \"%s\".",
					sa.sun_path);
		}
	}

	status = bind (sock_fd, (struct sockaddr *) &sa, sizeof (sa));
	if (status != 0)
	{
		char errbuf[1024];
		sstrerror (errno, errbuf, sizeof (errbuf));
		ERROR ("unixsock plugin: bind failed: %s", errbuf);
		close (sock_fd);
		sock_fd = -1;
		return (-1);
	}

	chmod (sa.sun_path, sock_perms);

	status = listen (sock_fd, 8);
	if (status != 0)
	{
		char errbuf[1024];
		ERROR ("unixsock plugin: listen failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		close (sock_fd);
		sock_fd = -1;
		return (-1);
	}

	do
	{
		char *grpname;
		struct group *g;
		struct group sg;
		char grbuf[2048];

		grpname = (sock_group != NULL) ? sock_group : COLLECTD_GRP_NAME;
		g = NULL;

		status = getgrnam_r (grpname, &sg, grbuf, sizeof (grbuf), &g);
		if (status != 0)
		{
			char errbuf[1024];
			WARNING ("unixsock plugin: getgrnam_r (%s) failed: %s", grpname,
					sstrerror (errno, errbuf, sizeof (errbuf)));
			break;
		}
		if (g == NULL)
		{
			WARNING ("unixsock plugin: No such group: `%s'",
					grpname);
			break;
		}

		if (chown ((sock_file != NULL) ? sock_file : US_DEFAULT_PATH,
					(uid_t) -1, g->gr_gid) != 0)
		{
			char errbuf[1024];
			WARNING ("unixsock plugin: chown (%s, -1, %i) failed: %s",
					(sock_file != NULL) ? sock_file : US_DEFAULT_PATH,
					(int) g->gr_gid,
					sstrerror (errno, errbuf, sizeof (errbuf)));
		}
	} while (0);

	return (0);
}