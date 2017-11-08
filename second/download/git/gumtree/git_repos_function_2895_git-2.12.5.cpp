static size_t rpc_out(void *ptr, size_t eltsize,
		size_t nmemb, void *buffer_)
{
	size_t max = eltsize * nmemb;
	struct rpc_state *rpc = buffer_;
	size_t avail = rpc->len - rpc->pos;

	if (!avail) {
		rpc->initial_buffer = 0;
		avail = packet_read(rpc->out, NULL, NULL, rpc->buf, rpc->alloc, 0);
		if (!avail)
			return 0;
		rpc->pos = 0;
		rpc->len = avail;
	}

	if (max < avail)
		avail = max;
	memcpy(ptr, rpc->buf + rpc->pos, avail);
	rpc->pos += avail;
	return avail;
}