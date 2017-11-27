static int tbl_config_append_array_i (char *name, int **var, size_t *len,
		oconfig_item_t *ci)
{
	int *tmp;

	size_t i;

	if (1 > ci->values_num) {
		log_err ("\"%s\" expects at least one argument.", name);
		return 1;
	}

	for (i = 0; i < ci->values_num; ++i) {
		if (OCONFIG_TYPE_NUMBER != ci->values[i].type) {
			log_err ("\"%s\" expects numerical arguments only.", name);
			return 1;
		}
	}

	*len += ci->values_num;
	tmp = (int *)realloc (*var, *len * sizeof (**var));
	if (NULL == tmp) {
		char errbuf[1024];
		log_err ("realloc failed: %s.",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return -1;
	}

	*var = tmp;

	for (i = *len - ci->values_num; i < *len; ++i)
		(*var)[i] = (int)ci->values[i].value.number;
	return 0;
}