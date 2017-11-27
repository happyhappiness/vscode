int ping_setopt (pingobj_t *obj, int option, void *value)
{
	int ret = 0;

	switch (option)
	{
		case PING_OPT_TIMEOUT:
			obj->timeout = *((double *) value);
			if (obj->timeout < 0.0)
			{
				obj->timeout = PING_DEF_TIMEOUT;
				ret = -1;
			}
			break;

		case PING_OPT_TTL:
			obj->ttl = *((int *) value);
			if ((obj->ttl < 1) || (obj->ttl > 255))
			{
				obj->ttl = PING_DEF_TTL;
				ret = -1;
			}
			break;

		case PING_OPT_AF:
			obj->addrfamily = *((int *) value);
			if ((obj->addrfamily != AF_UNSPEC)
					&& (obj->addrfamily != AF_INET)
					&& (obj->addrfamily != AF_INET6))
			{
				obj->addrfamily = PING_DEF_AF;
				ret = -1;
			}
			break;

		case PING_OPT_DATA:
			if (obj->data != NULL)
			{
				free (obj->data);
				obj->data = NULL;
			}
			obj->data = strdup ((const char *) value);
			break;

		default:
			ret = -2;
	} /* switch (option) */

	return (ret);
}