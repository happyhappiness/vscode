static void ping_set_error (pingobj_t *obj, const char *function,
	       	const char *message)
{
	snprintf (obj->errmsg, PING_ERRMSG_LEN, "%s: %s", function, message);
	obj->errmsg[PING_ERRMSG_LEN - 1] = '\0';
}