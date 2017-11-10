static int parse_attr(const char *name, int len)
{
	static const int attr_values[] = { 1, 2, 4, 5, 7,
					   22, 22, 24, 25, 27 };
	static const char * const attr_names[] = {
		"bold", "dim", "ul", "blink", "reverse",
		"nobold", "nodim", "noul", "noblink", "noreverse"
	};
	int i;
	for (i = 0; i < ARRAY_SIZE(attr_names); i++) {
		const char *str = attr_names[i];
		if (!strncasecmp(name, str, len) && !str[len])
			return attr_values[i];
	}
	return -1;
}