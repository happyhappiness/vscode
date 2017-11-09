int lp_number(char *name)
{
	int i;

	for (i = section_list.count - 1; i >= 0; i--) {
		if (strcmp(lp_name(i), name) == 0)
			break;
	}

	return i;
}