int check_capability (int capability) /* {{{ */
{
#ifdef _LINUX_CAPABILITY_VERSION_3
	cap_user_header_t cap_header = calloc(1, sizeof (*cap_header));
	if (cap_header == NULL)
	{
		ERROR("check_capability: calloc failed");
		return (-1);
	}

	cap_user_data_t cap_data = calloc(1, sizeof (*cap_data));
	if (cap_data == NULL)
	{
		ERROR("check_capability: calloc failed");
		sfree(cap_header);
		return (-1);
	}

	cap_header->pid = getpid();
	cap_header->version = _LINUX_CAPABILITY_VERSION;
	if (capget(cap_header, cap_data) < 0)
	{
		ERROR("check_capability: capget failed");
		sfree(cap_header);
		sfree(cap_data);
		return (-1);
	}

	if ((cap_data->effective & (1 << capability)) == 0)
	{
		sfree(cap_header);
		sfree(cap_data);
		return (-1);
	}
	else
	{
		sfree(cap_header);
		sfree(cap_data);
		return (0);
	}
#else
	WARNING ("check_capability: unsupported capability implementation. "
	    "Some plugin(s) may require elevated privileges to work properly.");
	return (0);
#endif /* _LINUX_CAPABILITY_VERSION_3 */
}