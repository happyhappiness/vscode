	} else
		return get_colorbool_found ? 0 : 1;
}

static void check_write(void)
{
	if (given_config_source.use_stdin)
		die("writing to stdin is not supported");

	if (given_config_source.blob)
		die("writing config blobs is not supported");
}
