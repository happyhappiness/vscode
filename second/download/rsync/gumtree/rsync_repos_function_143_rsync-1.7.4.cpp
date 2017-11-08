static void report(int f)
{
  int64 in,out,tsize;
  time_t t = time(NULL);
  
  if (!verbose) return;

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
    in = read_longint(f);
    out = read_longint(f);
    tsize = read_longint(f);
  }

#if HAVE_LONGLONG
  printf("wrote %lld bytes  read %lld bytes  %.2f bytes/sec\n",
	 (long long)out,(long long)in,(in+out)/(0.5 + (t-starttime)));
  printf("total size is %lld  speedup is %.2f\n",
	 (long long)tsize,(1.0*tsize)/(in+out));
#else
  printf("wrote %ld bytes  read %ld bytes  %.2f bytes/sec\n",
	 (long)out,(long)in,(in+out)/(0.5 + (t-starttime)));
  printf("total size is %ld  speedup is %.2f\n",
	 (long)tsize,(1.0*tsize)/(in+out));
#endif
}