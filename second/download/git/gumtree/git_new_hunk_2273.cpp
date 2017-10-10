	}

	return &c;
}
#endif

static int serve(struct string_list *listen_addr, int listen_port,
    struct credentials *cred)
{
	struct socketlist socklist = { NULL, 0, 0 };

	socksetup(listen_addr, listen_port, &socklist);
