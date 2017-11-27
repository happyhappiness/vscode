int service_name_to_port_number (const char *service_name)
{
	struct addrinfo *ai_list;
	int status;
	int service_number;

	if (service_name == NULL)
		return (-1);

	struct addrinfo ai_hints = {
		.ai_family = AF_UNSPEC
	};

	status = getaddrinfo (/* node = */ NULL, service_name,
			&ai_hints, &ai_list);
	if (status != 0)
	{
		ERROR ("service_name_to_port_number: getaddrinfo failed: %s",
				gai_strerror (status));
		return (-1);
	}

	service_number = -1;
	for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
	{
		if (ai_ptr->ai_family == AF_INET)
		{
			struct sockaddr_in *sa;

			sa = (void *) ai_ptr->ai_addr;
			service_number = (int) ntohs (sa->sin_port);
		}
		else if (ai_ptr->ai_family == AF_INET6)
		{
			struct sockaddr_in6 *sa;

			sa = (void *) ai_ptr->ai_addr;
			service_number = (int) ntohs (sa->sin6_port);
		}

		if ((service_number > 0) && (service_number <= 65535))
			break;
	}

	freeaddrinfo (ai_list);

	if ((service_number > 0) && (service_number <= 65535))
		return (service_number);
	return (-1);
}