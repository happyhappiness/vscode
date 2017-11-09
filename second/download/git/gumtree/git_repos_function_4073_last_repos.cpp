static int release_helper(struct transport *transport)
{
	int res = 0;
	struct helper_data *data = transport->data;
	free_refspec(data->refspec_nr, data->refspecs);
	data->refspecs = NULL;
	res = disconnect_helper(transport);
	free(transport->data);
	return res;
}