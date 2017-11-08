void wait_for_receiver(void)
{
	if (io_flush(NORMAL_FLUSH))
		return;
	read_msg_fd();
}