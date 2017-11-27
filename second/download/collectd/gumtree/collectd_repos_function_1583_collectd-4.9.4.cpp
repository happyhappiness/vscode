static int cipvs_shutdown (void)
{
	if (sockfd >= 0)
		close (sockfd);
	sockfd = -1;

	return 0;
}