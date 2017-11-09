static int map_parameter(char *parmname)
{
	int iIndex;

	if (*parmname == '-')
		return -1;

	for (iIndex = 0; parm_table[iIndex].label; iIndex++) {
		if (strwicmp(parm_table[iIndex].label, parmname) == 0)
			return iIndex;
	}

	rprintf(FLOG, "Unknown Parameter encountered: \"%s\"\n", parmname);
	return -1;
}