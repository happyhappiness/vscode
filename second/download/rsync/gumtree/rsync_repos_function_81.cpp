static void report(int f)
{
  int in,out,tsize;
  time_t t = time(NULL);
  
  if (!verbose) return;

  if (am_server && sender) {
    write_int(f,read_total());
    write_int(f,write_total());
    write_int(f,total_size);
    write_flush(f);
    return;
  }
    
  if (sender) {
    in = read_total();
    out = write_total();
    tsize = (int)total_size;
  } else {
    in = read_int(f);
    out = read_int(f);
    tsize = read_int(f);
  }

  printf("wrote %d bytes  read %d bytes  %g bytes/sec\n",
	 out,in,(in+out)/(0.5 + (t-starttime)));        
  printf("total size is %d  speedup is %g\n",
	 tsize,(1.0*tsize)/(in+out));
}