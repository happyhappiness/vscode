{
	if (type >= ARRAY_SIZE(object_type_strings))
		return NULL;
	return object_type_strings[type];
}

int type_from_string(const char *str)
{
	int i;

	for (i = 1; i < ARRAY_SIZE(object_type_strings); i++)
		if (!strcmp(str, object_type_strings[i]))
			return i;
	die("invalid object type \"%s\"", str);
}

/*
 * Return a numerical hash value between 0 and n-1 for the object with
 * the specified sha1.  n must be a power of 2.  Please note that the
