char *
cu_mount_getoptionvalue(char *line, char *keyword)
{
	char *r;

	r = cu_mount_checkoption(line, keyword, 0);
	if(r != NULL) {
		char *p;
		r += strlen(keyword);
		p = strchr(r, ',');
		if(p == NULL) {
			if(strlen(r) == 0) {
				return NULL;
			}
			return sstrdup(r);
		} else {
			char *m;
			if((p-r) == 1) {
				return NULL;
			}
			m = (char *)smalloc(p-r+1);
			sstrncpy(m, r, p-r+1);
			return m;
		}
	}
	return r;
}