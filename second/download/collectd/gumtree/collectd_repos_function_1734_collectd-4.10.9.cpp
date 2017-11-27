static int ts_destroy (void **user_data) /* {{{ */
{
	ts_data_t **data;

	if (user_data == NULL)
		return (-EINVAL);

	data = (ts_data_t **) user_data;

	free (*data);
	*data = NULL;

	return (0);
}