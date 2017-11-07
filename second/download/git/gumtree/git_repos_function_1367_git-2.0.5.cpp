int type_from_string(const char *str)
{
	int i;

	for (i = 1; i < ARRAY_SIZE(object_type_strings); i++)
		if (!strcmp(str, object_type_strings[i]))
			return i;
	die("invalid object type \"%s\"", str);
}