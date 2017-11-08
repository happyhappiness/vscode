int count_dir_elements(const char *p)
{
	int cnt = 0, new_component = 1;
	while (*p) {
		if (*p++ == '/')
			new_component = (*p != '.' || (p[1] != '/' && p[1] != '\0'));
		else if (new_component) {
			new_component = 0;
			cnt++;
		}
	}
	return cnt;
}