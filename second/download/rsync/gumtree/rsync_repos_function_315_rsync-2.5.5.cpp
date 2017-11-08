static int check_refuse_options(char *ref, int opt)
{
	int i, len;
	char *p;
	const char *name;

	for (i=0; long_options[i].longName; i++) {
		if (long_options[i].val == opt) break;
	}
	
	if (!long_options[i].longName) return 0;

	name = long_options[i].longName;
	len = strlen(name);

	while ((p = strstr(ref,name))) {
		if ((p==ref || p[-1]==' ') &&
		    (p[len] == ' ' || p[len] == 0)) {
			snprintf(err_buf,sizeof(err_buf),
				 "The '%s' option is not supported by this server\n", name);
			return 1;
		}
		ref += len;
	}
	return 0;
}