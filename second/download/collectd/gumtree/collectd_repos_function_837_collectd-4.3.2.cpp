int ping_send (pingobj_t *obj)
{
	int ret;

	if (ping_send_all (obj) < 0)
		return (-1);

	if ((ret = ping_receive_all (obj)) < 0)
		return (-2);

	return (ret);
}