		eol = strchr(body, '\n');
		len = eol ? eol - body : strlen(body);
		printf(" %.*s\n", (int) len, body);
	}
	else
		printf("\n");
	logmsg_free(msg, commit);
}

static void update_index_from_diff(struct diff_queue_struct *q,
		struct diff_options *opt, void *data)
{
	int i;
