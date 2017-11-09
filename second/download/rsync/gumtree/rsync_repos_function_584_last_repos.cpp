static void show_malloc_stats(void)
{
#ifdef HAVE_MALLINFO
	struct mallinfo mi;

	mi = mallinfo();

	rprintf(FCLIENT, "\n");
	rprintf(FINFO, RSYNC_NAME "[%d] (%s%s%s) heap statistics:\n",
		(int)getpid(), am_server ? "server " : "",
		am_daemon ? "daemon " : "", who_am_i());
	rprintf(FINFO, "  arena:     %10ld   (bytes from sbrk)\n",
		(long)mi.arena);
	rprintf(FINFO, "  ordblks:   %10ld   (chunks not in use)\n",
		(long)mi.ordblks);
	rprintf(FINFO, "  smblks:    %10ld\n",
		(long)mi.smblks);
	rprintf(FINFO, "  hblks:     %10ld   (chunks from mmap)\n",
		(long)mi.hblks);
	rprintf(FINFO, "  hblkhd:    %10ld   (bytes from mmap)\n",
		(long)mi.hblkhd);
	rprintf(FINFO, "  allmem:    %10ld   (bytes from sbrk + mmap)\n",
		(long)mi.arena + mi.hblkhd);
	rprintf(FINFO, "  usmblks:   %10ld\n",
		(long)mi.usmblks);
	rprintf(FINFO, "  fsmblks:   %10ld\n",
		(long)mi.fsmblks);
	rprintf(FINFO, "  uordblks:  %10ld   (bytes used)\n",
		(long)mi.uordblks);
	rprintf(FINFO, "  fordblks:  %10ld   (bytes free)\n",
		(long)mi.fordblks);
	rprintf(FINFO, "  keepcost:  %10ld   (bytes in releasable chunk)\n",
		(long)mi.keepcost);
#endif /* HAVE_MALLINFO */
}