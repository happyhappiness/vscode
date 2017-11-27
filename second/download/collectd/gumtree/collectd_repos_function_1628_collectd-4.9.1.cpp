static int ts_destroy (void **user_data) /* {{{ */
{
	if (user_data == NULL)
		return (-EINVAL);

	free (*user_data);
	*user_data = NULL;

	return (0);
}