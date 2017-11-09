static int serve(struct string_list *listen_addr, int listen_port,
    struct credentials *cred)
{
	struct socketlist socklist = { NULL, 0, 0 };

	socksetup(listen_addr, listen_port, &socklist);
	if (socklist.nr == 0)
		die("unable to allocate any listen sockets on port %u",
		    listen_port);

	drop_privileges(cred);

	loginfo("Ready to rumble");

	return service_loop(&socklist);
}