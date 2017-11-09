static int get_sockaddr_family(const struct sockaddr_storage *ss)
{
	return ((struct sockaddr *) ss)->sa_family;
}