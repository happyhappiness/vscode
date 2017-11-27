static int riemann_disconnect (struct riemann_host *host) /* {{{ */
{
	if ((host->flags & F_CONNECT) == 0)
		return (0);

	close (host->s);
	host->s = -1;
	host->flags &= ~F_CONNECT;

	return (0);
}