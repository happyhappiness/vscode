static curlioerr rpc_ioctl(CURL *handle, int cmd, void *clientp)
{
	struct rpc_state *rpc = clientp;

	switch (cmd) {
	case CURLIOCMD_NOP:
		return CURLIOE_OK;

	case CURLIOCMD_RESTARTREAD:
		if (rpc->initial_buffer) {
			rpc->pos = 0;
			return CURLIOE_OK;
		}
		fprintf(stderr, "Unable to rewind rpc post data - try increasing http.postBuffer\n");
		return CURLIOE_FAILRESTART;

	default:
		return CURLIOE_UNKNOWNCMD;
	}
}