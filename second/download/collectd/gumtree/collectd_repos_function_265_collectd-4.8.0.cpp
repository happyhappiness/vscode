static int mr_destroy (void **user_data) /* {{{ */
{
	if ((user_data != NULL) && (*user_data != NULL))
		mr_free_match (*user_data);
	return (0);
}