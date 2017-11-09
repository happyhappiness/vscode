static void consume_shallow_list(struct fetch_pack_args *args, int fd)
{
	if (args->stateless_rpc && args->deepen) {
		/* If we sent a depth we will get back "duplicate"
		 * shallow and unshallow commands every time there
		 * is a block of have lines exchanged.
		 */
		char *line;
		while ((line = packet_read_line(fd, NULL))) {
			if (starts_with(line, "shallow "))
				continue;
			if (starts_with(line, "unshallow "))
				continue;
			die(_("git fetch-pack: expected shallow list"));
		}
	}
}