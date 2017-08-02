{
	int i;

	for (i = 0; codes[i].code != -1; i++) {
		if (code == codes[i].code)
			return ((codes[i].setter)(a));
	}

	archive_set_error(a, EINVAL, "No such filter");
	return (ARCHIVE_FATAL);
}