		return NULL;
	default:
		return strbuf_detach(&ret, NULL);
	}
}

static void parse_argv(struct argv_array *out, const char *arg, const char *service)
{
	while (*arg) {
		char *expanded = strip_escapes(arg, service, &arg);
		if (expanded)
			argv_array_push(out, expanded);
		free(expanded);
	}
}

static void send_git_request(int stdin_fd, const char *serv, const char *repo,
	const char *vhost)
{
	if (!vhost)
