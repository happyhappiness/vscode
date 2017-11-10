static int disconnect_helper(struct transport *transport)
{
	struct helper_data *data = transport->data;
	int res = 0;

	if (data->helper) {
		if (debug)
			fprintf(stderr, "Debug: Disconnecting.\n");
		if (!data->no_disconnect_req) {
			/*
			 * Ignore write errors; there's nothing we can do,
			 * since we're about to close the pipe anyway. And the
			 * most likely error is EPIPE due to the helper dying
			 * to report an error itself.
			 */
			sigchain_push(SIGPIPE, SIG_IGN);
			xwrite(data->helper->in, "\n", 1);
			sigchain_pop(SIGPIPE);
		}
		close(data->helper->in);
		close(data->helper->out);
		fclose(data->out);
		res = finish_command(data->helper);
		free(data->helper);
		data->helper = NULL;
	}
	return res;
}