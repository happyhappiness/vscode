static int ping_send_all (pingobj_t *obj)
{
	pinghost_t *ph;
	pinghost_t *ptr;

	int ret;

	ret = 0;
	ph = obj->head;

	for (ptr = ph; ptr != NULL; ptr = ptr->next)
	{
		/* start timer.. The GNU `ping6' starts the timer before
		 * sending the packet, so I will do that too */
		if (gettimeofday (ptr->timer, NULL) == -1)
		{
			dprintf ("gettimeofday: %s\n", strerror (errno));
			timerclear (ptr->timer);
			ret--;
			continue;
		}
		else
		{
			dprintf ("timer set for hostname = %s\n", ptr->hostname);
		}

		if (ptr->addrfamily == AF_INET6)
		{	
			dprintf ("Sending ICMPv6 echo request to `%s'\n", ptr->hostname);
			if (ping_send_one_ipv6 (obj, ptr) != 0)
			{
				timerclear (ptr->timer);
				ret--;
				continue;
			}
		}
		else if (ptr->addrfamily == AF_INET)
		{
			dprintf ("Sending ICMPv4 echo request to `%s'\n", ptr->hostname);
			if (ping_send_one_ipv4 (obj, ptr) != 0)
			{
				timerclear (ptr->timer);
				ret--;
				continue;
			}
		}
		else /* this should not happen */
		{
			dprintf ("Unknown address family: %i\n", ptr->addrfamily);
			timerclear (ptr->timer);
			ret--;
			continue;
		}

		ptr->sequence++;
	}

	return (ret);
}