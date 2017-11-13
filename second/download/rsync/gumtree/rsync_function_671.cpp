static void send_listing(int fd)
{
	int n = lp_numservices();
	int i;
	extern int remote_version;

	for (i=0;i<n;i++)
		if (lp_list(i))
		    io_printf(fd, "%-15s\t%s\n", lp_name(i), lp_comment(i));

	if (remote_version >= 25)
		io_printf(fd,"@RSYNCD: EXIT\n");
}