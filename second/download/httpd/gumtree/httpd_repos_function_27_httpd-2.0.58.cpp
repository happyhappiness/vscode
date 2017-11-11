void output_results()
{
  int timetaken;
  
  gettimeofday(&endtime,0);
  timetaken = timedif(endtime, start);
  
  printf("\n---\n");
  printf("Server:                 %s\n", server_name);
  printf("Document Length:        %d\n", doclen);  
  printf("Concurency Level:       %d\n", concurrency);
  printf("Time taken for tests:   %d.%03d seconds\n", 
	 timetaken/1000, timetaken%1000);
  printf("Complete requests:      %d\n", done);
  printf("Failed requests:        %d\n", bad);
  if(bad) printf("   (Connect: %d, Length: %d, Exceptions: %d)\n",
		 err_conn, err_length, err_except);
  if(keepalive) printf("Keep-Alive requests:    %d\n", doneka);
  printf("Bytes transfered:       %d\n", totalread);
  printf("HTML transfered:        %d\n", totalbread);
  
  /* avoid divide by zero */
  if(timetaken) {
    printf("Requests per seconds:   %.2f\n", 1000*(float)(done)/timetaken);
    printf("Transfer rate:          %.2f kb/s\n", 
	   (float)(totalread)/timetaken);
  }

  {
    /* work out connection times */
    int i;
    int totalcon=0, total=0;
    int mincon=9999999, mintot=999999;
    int maxcon=0, maxtot=0;

    for(i=0; i<requests; i++) {
      struct data s = stats[i];
      mincon = min(mincon, s.ctime);
      mintot = min(mintot, s.time);
      maxcon = max(maxcon, s.ctime);
      maxtot = max(maxtot, s.time);
      totalcon += s.ctime;
      total += s.time;
    }
    printf("\nConnnection Times (ms)\n");
    printf("           min   avg   max\n");
    printf("Connect: %5d %5d %5d\n",mincon, totalcon/requests, maxcon );
    printf("Total:   %5d %5d %5d\n", mintot, total/requests, maxtot);
    printf("---\n\n");
  }

  exit(0);
}