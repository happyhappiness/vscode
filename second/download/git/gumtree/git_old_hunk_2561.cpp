
		write_or_die(1, buf.buf, buf.len);
	}
	strbuf_release(&buf);
}

int cmd_send_pack(int argc, const char **argv, const char *prefix)
{
	int i, nr_refspecs = 0;
	const char **refspecs = NULL;
	const char *remote_name = NULL;
	struct remote *remote = NULL;
