}

static void objreport(struct object *obj, const char *msg_type,
			const char *err)
{
	fprintf(stderr, "%s in %s %s: %s\n",
		msg_type, printable_type(obj), describe_object(obj), err);
}

static int objerror(struct object *obj, const char *err)
{
	errors_found |= ERROR_OBJECT;
	objreport(obj, "error", err);
