char *
cu_mount_checkoption(char *line, const char *keyword, int full)
{
	char *line2, *l2, *p1, *p2;
	int l;

	if(line == NULL || keyword == NULL) {
		return NULL;
	}

	if(full != 0) {
		full = 1;
	}

	line2 = sstrdup(line);
	l2 = line2;
	while(*l2 != '\0') {
		if(*l2 == ',') {
			*l2 = '\0';
		}
		l2++;
	}

	l = strlen(keyword);
	p1 = line - 1;
	p2 = strchr(line, ',');
	do {
		if(strncmp(line2+(p1-line)+1, keyword, l+full) == 0) {
			free(line2);
			return p1+1;
		}
		p1 = p2;
		if(p1 != NULL) {
			p2 = strchr(p1+1, ',');
		}
	} while(p1 != NULL);

	free(line2);
	return NULL;
}