	{
		char buf[BUFERROR_BUF];

		buferror(buf, sizeof(buf));
		malloc_printf("<jemalloc>: Error in "
#ifdef _WIN32
		              "VirtualFree"
