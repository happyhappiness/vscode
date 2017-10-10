}

static void send_git_request(int stdin_fd, const char *serv, const char *repo,
	const char *vhost)
{
	if (!vhost)
		packet_write_fmt(stdin_fd, "%s %s%c", serv, repo, 0);
	else
		packet_write_fmt(stdin_fd, "%s %s%chost=%s%c", serv, repo, 0,
			     vhost, 0);
}

static int run_child(const char *arg, const char *service)
{
	int r;
