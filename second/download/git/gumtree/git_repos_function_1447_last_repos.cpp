static inline void *
diff_delta(const void *src_buf, unsigned long src_bufsize,
	   const void *trg_buf, unsigned long trg_bufsize,
	   unsigned long *delta_size, unsigned long max_delta_size)
{
	struct delta_index *index = create_delta_index(src_buf, src_bufsize);
	if (index) {
		void *delta = create_delta(index, trg_buf, trg_bufsize,
					   delta_size, max_delta_size);
		free_delta_index(index);
		return delta;
	}
	return NULL;
}