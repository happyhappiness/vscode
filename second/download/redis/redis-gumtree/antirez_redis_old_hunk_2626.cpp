		malloc_cprintf(write_cb, cbopaque, "CPUs: %u\n", ncpus);

		CTL_GET("arenas.narenas", &uv, unsigned);
		malloc_cprintf(write_cb, cbopaque, "Max arenas: %u\n", uv);

		malloc_cprintf(write_cb, cbopaque, "Pointer size: %zu\n",
		    sizeof(void *));
