				die_errno("unable to connect to cache daemon");
		}
	}
	strbuf_release(&buf);
}

int cmd_main(int argc, const char **argv)
{
	char *socket_path = NULL;
	int timeout = 900;
	const char *op;
	const char * const usage[] = {
