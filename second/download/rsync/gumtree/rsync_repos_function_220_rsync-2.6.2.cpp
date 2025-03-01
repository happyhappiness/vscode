void clean_fname(char *name)
{
	char *p;
	int l;
	int modified = 1;

	if (!name) return;

	while (modified) {
		modified = 0;

		if ((p = strstr(name,"/./")) != NULL) {
			modified = 1;
			while (*p) {
				p[0] = p[2];
				p++;
			}
		}

		if ((p = strstr(name,"//")) != NULL) {
			modified = 1;
			while (*p) {
				p[0] = p[1];
				p++;
			}
		}

		if (strncmp(p = name, "./", 2) == 0) {
			modified = 1;
			do {
				p[0] = p[2];
			} while (*p++);
		}

		l = strlen(p = name);
		if (l > 1 && p[l-1] == '/') {
			modified = 1;
			p[l-1] = 0;
		}
	}
}