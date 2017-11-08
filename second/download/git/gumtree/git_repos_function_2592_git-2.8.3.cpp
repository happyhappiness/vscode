static size_t rpc_in(char *ptr, size_t eltsize,
		size_t nmemb, void *buffer_)
{
	size_t size = eltsize * nmemb;
	struct rpc_state *rpc = buffer_;
	write_or_die(rpc->in, ptr, size);
	return size;
}