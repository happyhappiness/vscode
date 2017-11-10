static void avoid_racy(void)
{
	/*
	 * not use if we could usleep(10) if USE_NSEC is defined. The
	 * field nsec could be there, but the OS could choose to
	 * ignore it?
	 */
	sleep(1);
}