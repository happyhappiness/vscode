print_buffer(first, last, "%6.1f / %6.1f MB",
		       (double)d->download()->bytes_done() / (double)(1 << 20),
		       (double)d->download()->bytes_total() / (double)(1 << 20));