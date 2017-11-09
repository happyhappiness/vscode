void sigchain_push_common(sigchain_fun f)
{
	sigchain_push(SIGINT, f);
	sigchain_push(SIGHUP, f);
	sigchain_push(SIGTERM, f);
	sigchain_push(SIGQUIT, f);
	sigchain_push(SIGPIPE, f);
}