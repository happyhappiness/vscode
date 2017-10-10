		string_list_clear(&cap_list, 0);
	}

done:
	sigchain_pop(SIGPIPE);

	return err;
}

static int apply_multi_file_filter(const char *path, const char *src, size_t len,
				   int fd, struct strbuf *dst, const char *cmd,
				   const unsigned int wanted_capability)
{
