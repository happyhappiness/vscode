static void report(int f)
{
	int64 in,out,tsize;
	time_t t = time(NULL);
	extern int am_server;
	extern int am_sender;
	extern int am_daemon;

	if (!verbose) return;

	if (am_daemon) {
		rprintf(FINFO, "wrote %.0f bytes  read %.0f bytes  total size %.0f\n",
			(double)write_total(),(double)read_total(),
			(double)total_size);
	}

	if (am_server && am_sender) {
		write_longint(f,read_total());
		write_longint(f,write_total());
		write_longint(f,total_size);
		write_flush(f);
		return;
	}
    
	if (am_sender) {
		in = read_total();
		out = write_total();
		tsize = total_size;
	} else {
		out = read_longint(f);
		in = read_longint(f);
		tsize = read_longint(f);
	}
	
	printf("wrote %.0f bytes  read %.0f bytes  %.2f bytes/sec\n",
	       (double)out,(double)in,(in+out)/(0.5 + (t-starttime)));
	printf("total size is %.0f  speedup is %.2f\n",
	       (double)tsize,(1.0*tsize)/(in+out));
}