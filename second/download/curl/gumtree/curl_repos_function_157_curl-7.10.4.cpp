int Curl_pgrsUpdate(struct connectdata *conn)
{
  struct timeval now;
  int result;

  char max5[6][10];
  double dlpercen=0;
  double ulpercen=0;
  double total_percen=0;

  double total_transfer;
  double total_expected_transfer;
  double timespent;

  struct SessionHandle *data = conn->data;

  int nowindex = data->progress.speeder_c% CURR_TIME;
  int checkindex;

  int countindex; /* amount of seconds stored in the speeder array */

  char time_left[10];
  char time_total[10];
  char time_current[10];
      
  double ulestimate=0;
  double dlestimate=0;
  
  double total_estimate;


  if(data->progress.flags & PGRS_HIDE)
    ; /* We do enter this function even if we don't wanna see anything, since
         this is were lots of the calculations are being made that will be used
         even when not displayed! */
  else if(!(data->progress.flags & PGRS_HEADERS_OUT)) {
    if (!data->progress.callback) {
      if(conn->resume_from)
        fprintf(data->set.err, "** Resuming transfer from byte position %d\n",
                conn->resume_from);
      fprintf(data->set.err,
              "  %% Total    %% Received %% Xferd  Average Speed          Time             Curr.\n"
              "                                 Dload  Upload Total    Current  Left    Speed\n");
    }
    data->progress.flags |= PGRS_HEADERS_OUT; /* headers are shown */
  }

  now = Curl_tvnow(); /* what time is it */

  /* The exact time spent so far (from the start) */
  timespent = (double)Curl_tvdiff (now, data->progress.start)/1000;

  data->progress.timespent = timespent;

  /* The average download speed this far */
  data->progress.dlspeed =
    data->progress.downloaded/(timespent>0.01?timespent:1);

  /* The average upload speed this far */
  data->progress.ulspeed =
    data->progress.uploaded/(timespent>0.01?timespent:1);

  if(data->progress.lastshow == Curl_tvlong(now))
    return 0; /* never update this more than once a second if the end isn't 
                 reached */
  data->progress.lastshow = now.tv_sec;

  /* Let's do the "current speed" thing, which should use the fastest
     of the dl/ul speeds. Store the fasted speed at entry 'nowindex'. */
  data->progress.speeder[ nowindex ] =
    data->progress.downloaded>data->progress.uploaded?
    data->progress.downloaded:data->progress.uploaded;

  /* remember the exact time for this moment */
  data->progress.speeder_time [ nowindex ] = now;

  /* advance our speeder_c counter, which is increased every time we get
     here and we expect it to never wrap as 2^32 is a lot of seconds! */
  data->progress.speeder_c++;

  /* figure out how many index entries of data we have stored in our speeder
     array. With N_ENTRIES filled in, we have about N_ENTRIES-1 seconds of
     transfer. Imagine, after one second we have filled in two entries,
     after two seconds we've filled in three entries etc. */
  countindex = ((data->progress.speeder_c>=CURR_TIME)?
                CURR_TIME:data->progress.speeder_c) - 1;

  /* first of all, we don't do this if there's no counted seconds yet */
  if(countindex) {
    long span_ms;

    /* Get the index position to compare with the 'nowindex' position.
       Get the oldest entry possible. While we have less than CURR_TIME
       entries, the first entry will remain the oldest. */
    checkindex = (data->progress.speeder_c>=CURR_TIME)?
      data->progress.speeder_c%CURR_TIME:0;

    /* Figure out the exact time for the time span */
    span_ms = Curl_tvdiff(now,
                          data->progress.speeder_time[checkindex]);
    if(0 == span_ms)
      span_ms=1; /* at least one millisecond MUST have passed */

    /* Calculate the average speed the last 'countindex' seconds */
    data->progress.current_speed =
      (data->progress.speeder[nowindex]-
       data->progress.speeder[checkindex])/((double)span_ms/1000);
  }
  else
    /* the first second we use the main average */
    data->progress.current_speed =
      (data->progress.ulspeed>data->progress.dlspeed)?
      data->progress.ulspeed:data->progress.dlspeed;

  if(data->progress.flags & PGRS_HIDE)
    return 0;

  else if(data->set.fprogress) {
    /* There's a callback set, so we call that instead of writing
       anything ourselves. This really is the way to go. */
    result= data->set.fprogress(data->set.progress_client,
                                data->progress.size_dl,
                                data->progress.downloaded,
                                data->progress.size_ul,
                                data->progress.uploaded);
    if(result)
      failf(data, "Callback aborted");
    return result;
  }

  /* Figure out the estimated time of arrival for the upload */
  if((data->progress.flags & PGRS_UL_SIZE_KNOWN) && data->progress.ulspeed){
    ulestimate = data->progress.size_ul / data->progress.ulspeed;
    ulpercen = (data->progress.uploaded / data->progress.size_ul)*100;
  }

  /* ... and the download */
  if((data->progress.flags & PGRS_DL_SIZE_KNOWN) && data->progress.dlspeed) {
    dlestimate = data->progress.size_dl / data->progress.dlspeed;
    dlpercen = (data->progress.downloaded / data->progress.size_dl)*100;
  }
    
  /* Now figure out which of them that is slower and use for the for
     total estimate! */
  total_estimate = ulestimate>dlestimate?ulestimate:dlestimate;


  /* If we have a total estimate, we can display that and the expected
     time left */
  if(total_estimate) {
    time2str(time_left, (int)(total_estimate - data->progress.timespent)); 
    time2str(time_total, (int)total_estimate);
  }
  else {
    /* otherwise we blank those times */
    strcpy(time_left,  "--:--:--");
    strcpy(time_total, "--:--:--");
  }
  /* The time spent so far is always known */
  time2str(time_current, (int)data->progress.timespent);

  /* Get the total amount of data expected to get transfered */
  total_expected_transfer = 
    (data->progress.flags & PGRS_UL_SIZE_KNOWN?
     data->progress.size_ul:data->progress.uploaded)+
    (data->progress.flags & PGRS_DL_SIZE_KNOWN?
     data->progress.size_dl:data->progress.downloaded);
      
  /* We have transfered this much so far */
  total_transfer = data->progress.downloaded + data->progress.uploaded;

  /* Get the percentage of data transfered so far */
  if(total_expected_transfer)
    total_percen=(double)(total_transfer/total_expected_transfer)*100;

  fprintf(data->set.err,
          "\r%3d %s  %3d %s  %3d %s  %s  %s %s %s %s %s",
          (int)total_percen,                            /* total % */
          max5data(total_expected_transfer, max5[2]),   /* total size */
          (int)dlpercen,                                /* rcvd % */
          max5data(data->progress.downloaded, max5[0]), /* rcvd size */
          (int)ulpercen,                                /* xfer % */
          max5data(data->progress.uploaded, max5[1]),   /* xfer size */

          max5data(data->progress.dlspeed, max5[3]), /* avrg dl speed */
          max5data(data->progress.ulspeed, max5[4]), /* avrg ul speed */
          time_total,                           /* total time */
          time_current,                         /* current time */
          time_left,                            /* time left */
          max5data(data->progress.current_speed, max5[5]) /* current speed */
          );

  /* we flush the output stream to make it appear as soon as possible */
  fflush(data->set.err);

  return 0;
}