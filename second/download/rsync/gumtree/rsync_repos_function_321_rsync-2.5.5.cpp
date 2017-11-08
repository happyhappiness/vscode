static void show_malloc_stats(void)
{
#ifdef HAVE_MALLINFO
	struct mallinfo mi;
	extern int am_server;
	extern int am_sender;
	extern int am_daemon;

	mi = mallinfo();

	rprintf(FINFO, RSYNC_NAME "[%d] (%s%s%s) heap statistics:\n",
		getpid(),
		am_server ? "server " : "",
		am_daemon ? "daemon " : "",
		am_sender ? "sender" : "receiver");
	rprintf(FINFO, "  arena:     %10d   (bytes from sbrk)\n", mi.arena);
	rprintf(FINFO, "  ordblks:   %10d   (chunks not in use)\n", mi.ordblks);
	rprintf(FINFO, "  smblks:    %10d\n", mi.smblks);
	rprintf(FINFO, "  hblks:     %10d   (chunks from mmap)\n", mi.hblks);
	rprintf(FINFO, "  hblkhd:    %10d   (bytes from mmap)\n", mi.hblkhd);
	rprintf(FINFO, "  usmblks:   %10d\n", mi.usmblks);
	rprintf(FINFO, "  fsmblks:   %10d\n", mi.fsmblks);
	rprintf(FINFO, "  uordblks:  %10d   (bytes used)\n", mi.uordblks);
	rprintf(FINFO, "  fordblks:  %10d   (bytes free)\n", mi.fordblks);
	rprintf(FINFO, "  keepcost:  %10d   (bytes in releasable chunk)\n", mi.keepcost);
#endif /* HAVE_MALLINFO */
}