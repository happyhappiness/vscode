static void do_take_over(struct transport *transport)
{
	struct helper_data *data;
	data = (struct helper_data *)transport->data;
	transport_take_over(transport, data->helper);
	fclose(data->out);
	free(data);
}