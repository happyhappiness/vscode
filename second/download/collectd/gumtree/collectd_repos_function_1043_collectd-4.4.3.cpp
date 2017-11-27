pingobj_t *ping_construct (void)
{
	pingobj_t *obj;

	if ((obj = (pingobj_t *) malloc (sizeof (pingobj_t))) == NULL)
		return (NULL);
	memset (obj, '\0', sizeof (pingobj_t));

	obj->timeout    = PING_DEF_TIMEOUT;
	obj->ttl        = PING_DEF_TTL;
	obj->addrfamily = PING_DEF_AF;
	obj->data       = strdup (PING_DEF_DATA);

	return (obj);
}