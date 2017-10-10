			char *end;
			opts->depth = strtol(value, &end, 0);
			if (*end)
				die("transport: invalid depth option '%s'", value);
		}
		return 0;
	}
	return 1;
}

static int connect_setup(struct transport *transport, int for_push, int verbose)
{
