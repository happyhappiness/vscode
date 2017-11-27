static int parse_packet (void *buffer, int buffer_len)
{
	int status;

	value_list_t vl = VALUE_LIST_INIT;
	notification_t n;

	DEBUG ("network plugin: parse_packet: buffer = %p; buffer_len = %i;",
			buffer, buffer_len);

	memset (&vl, '\0', sizeof (vl));
	memset (&n, '\0', sizeof (n));
	status = 0;

	while ((status == 0) && (0 < buffer_len)
			&& ((unsigned int) buffer_len > sizeof (part_header_t)))
	{
		uint16_t pkg_length;
		uint16_t pkg_type;

		memcpy ((void *) &pkg_type,
				(void *) buffer,
				sizeof (pkg_type));
		memcpy ((void *) &pkg_length,
				(void *) (buffer + sizeof (pkg_type)),
				sizeof (pkg_length));

		pkg_length = ntohs (pkg_length);
		pkg_type = ntohs (pkg_type);

		if (pkg_length > buffer_len)
			break;
		/* Ensure that this loop terminates eventually */
		if (pkg_length < (2 * sizeof (uint16_t)))
			break;

		if (pkg_type == TYPE_VALUES)
		{
			status = parse_part_values (&buffer, &buffer_len,
					&vl.values, &vl.values_len);

			if (status != 0)
				break;

			if ((vl.time > 0)
					&& (strlen (vl.host) > 0)
					&& (strlen (vl.plugin) > 0)
					&& (strlen (vl.type) > 0)
					&& (cache_check (&vl) == 0))
			{
				plugin_dispatch_values (&vl);
			}
			else
			{
				DEBUG ("network plugin: parse_packet:"
						" NOT dispatching values");
			}

			sfree (vl.values);
		}
		else if (pkg_type == TYPE_TIME)
		{
			uint64_t tmp = 0;
			status = parse_part_number (&buffer, &buffer_len,
					&tmp);
			if (status == 0)
			{
				vl.time = (time_t) tmp;
				n.time = (time_t) tmp;
			}
		}
		else if (pkg_type == TYPE_INTERVAL)
		{
			uint64_t tmp = 0;
			status = parse_part_number (&buffer, &buffer_len,
					&tmp);
			if (status == 0)
				vl.interval = (int) tmp;
		}
		else if (pkg_type == TYPE_HOST)
		{
			status = parse_part_string (&buffer, &buffer_len,
					vl.host, sizeof (vl.host));
			if (status == 0)
				sstrncpy (n.host, vl.host, sizeof (n.host));
		}
		else if (pkg_type == TYPE_PLUGIN)
		{
			status = parse_part_string (&buffer, &buffer_len,
					vl.plugin, sizeof (vl.plugin));
			if (status == 0)
				sstrncpy (n.plugin, vl.plugin,
						sizeof (n.plugin));
		}
		else if (pkg_type == TYPE_PLUGIN_INSTANCE)
		{
			status = parse_part_string (&buffer, &buffer_len,
					vl.plugin_instance,
					sizeof (vl.plugin_instance));
			if (status == 0)
				sstrncpy (n.plugin_instance,
						vl.plugin_instance,
						sizeof (n.plugin_instance));
		}
		else if (pkg_type == TYPE_TYPE)
		{
			status = parse_part_string (&buffer, &buffer_len,
					vl.type, sizeof (vl.type));
			if (status == 0)
				sstrncpy (n.type, vl.type, sizeof (n.type));
		}
		else if (pkg_type == TYPE_TYPE_INSTANCE)
		{
			status = parse_part_string (&buffer, &buffer_len,
					vl.type_instance,
					sizeof (vl.type_instance));
			if (status == 0)
				sstrncpy (n.type_instance, vl.type_instance,
						sizeof (n.type_instance));
		}
		else if (pkg_type == TYPE_MESSAGE)
		{
			status = parse_part_string (&buffer, &buffer_len,
					n.message, sizeof (n.message));

			if (status != 0)
			{
				/* do nothing */
			}
			else if ((n.severity != NOTIF_FAILURE)
					&& (n.severity != NOTIF_WARNING)
					&& (n.severity != NOTIF_OKAY))
			{
				INFO ("network plugin: "
						"Ignoring notification with "
						"unknown severity %i.",
						n.severity);
			}
			else if (n.time <= 0)
			{
				INFO ("network plugin: "
						"Ignoring notification with "
						"time == 0.");
			}
			else if (strlen (n.message) <= 0)
			{
				INFO ("network plugin: "
						"Ignoring notification with "
						"an empty message.");
			}
			else
			{
				plugin_dispatch_notification (&n);
			}
		}
		else if (pkg_type == TYPE_SEVERITY)
		{
			uint64_t tmp = 0;
			status = parse_part_number (&buffer, &buffer_len,
					&tmp);
			if (status == 0)
				n.severity = (int) tmp;
		}
		else
		{
			DEBUG ("network plugin: parse_packet: Unknown part"
					" type: 0x%04hx", pkg_type);
			buffer = ((char *) buffer) + pkg_length;
		}
	} /* while (buffer_len > sizeof (part_header_t)) */

	return (status);
}