static void trace_write(struct trace_key *key, const void *buf, unsigned len)
{
	if (write_in_full(get_trace_fd(key), buf, len) < 0) {
		normalize_trace_key(&key);
		warning("unable to write trace for %s: %s",
			key->key, strerror(errno));
		trace_disable(key);
	}
}