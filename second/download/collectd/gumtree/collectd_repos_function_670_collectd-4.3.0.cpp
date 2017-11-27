static void *receive_thread (void *arg)
{
	return (network_receive () ? (void *) 1 : (void *) 0);
}