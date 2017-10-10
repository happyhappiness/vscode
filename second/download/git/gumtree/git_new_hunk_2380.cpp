		}
	}

done:
	git_inflate_end(&stream);
	close(out);
	free(full_request);
}

static void copy_request(const char *prog_name, int out)
{
	unsigned char *buf;
	ssize_t n = read_request(0, &buf);
	if (n < 0)
		die_errno("error reading request body");
	if (write_in_full(out, buf, n) != n)
		die("%s aborted reading request", prog_name);
	close(out);
	free(buf);
}

static void run_service(const char **argv, int buffer_input)
{
	const char *encoding = getenv("HTTP_CONTENT_ENCODING");
	const char *user = getenv("REMOTE_USER");
	const char *host = getenv("REMOTE_ADDR");
	int gzipped_request = 0;
	struct child_process cld = CHILD_PROCESS_INIT;
