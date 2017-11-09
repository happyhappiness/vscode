static int getsectionbyname(char *name)
{
	int i;

	for (i = section_list.count - 1; i >= 0; i--) {
		if (strwicmp(iSECTION(i).name, name) == 0)
			break;
	}

	return i;
}