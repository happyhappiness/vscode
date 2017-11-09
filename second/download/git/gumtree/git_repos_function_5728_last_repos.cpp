static int run_child(const char *arg, const char *service)
{
	int r;
	struct child_process child = CHILD_PROCESS_INIT;

	child.in = -1;
	child.out = -1;
	child.err = 0;
	parse_argv(&child.args, arg, service);

	if (start_command(&child) < 0)
		die("Can't run specified command");

	if (git_req)
		send_git_request(child.in, service, git_req, git_req_vhost);

	r = bidirectional_transfer_loop(child.out, child.in);
	if (!r)
		r = finish_command(&child);
	else
		finish_command(&child);
	return r;
}