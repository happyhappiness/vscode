static int config_set_i (char *name, int *var,
		const oconfig_item_t *ci, int min)
{
	int value;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_NUMBER != ci->values[0].type)) {
		log_err ("%s expects a single number argument.", name);
		return 1;
	}

	value = (int)ci->values[0].value.number;

	if (value < min) {
		log_err ("%s expects a number greater or equal to %i.", name, min);
		return 1;
	}

	*var = value;
	return 0;
}