int Curl_pgrsUpdate(struct connectdata *conn)
{
  struct curltime now;
  int result;
  char max5[6][10];
  curl_off_t dlpercen = 0;
  curl_off_t ulpercen = 0;
  curl_off_t total_percen = 0;
  curl_off_t total_transfer;
  curl_off_t total_expected_transfer;
  curl_off_t timespent;
  struct Curl_easy *data = conn->data;
  int nowindex = data->progress.speeder_c% CURR_TIME;
  int checkindex;
  int countindex; /* amount of seconds stored in the speeder array */
  char time_left[10];
  char time_total[10];
  char time_spent[10];
  curl_off_t ulestimate = 0;
  curl_off_t dlestimate = 0;
  curl_off_t total_estimate;
  bool shownow = FALSE;

  now = Curl_tvnow(); /* what time is it */

  /* The time spent so far (from the start) */
  data->progress.timespent = Curl_tvdiff_us(now, data->progress.start);
  timespent = (curl_off_t)data->progress.timespent/1000000; /* seconds */

  /* The average download speed this far */
  data->progress.dlspeed = (curl_off_t)
    (data->progress.downloaded/
     (timespent>0?timespent:1));

  /* The average upload speed this far */
  data->progress.ulspeed = (curl_off_t)
    (data->progress.uploaded/
     (timespent>0?timespent:1));

  /* Calculations done at most once a second, unless end is reached */
  if(data->progress.lastshow != now.tv_sec) {
    shownow = TRUE;

    data->progress.lastshow = now.tv_sec;

    /* Let's do the "current speed" thing, with the dl + ul speeds
       combined. Store the speed at entry 'nowindex'. */
    data->progress.speeder[ nowindex ] =
      data->progress.downloaded + data->progress.uploaded;

    /* remember the exact time for this moment */
    data->progress.speeder_time [ nowindex ] = now;

    /* advance our speeder_c counter, which is increased every time we get
       here and we expect it to never wrap as 2^32 is a lot of seconds! */
    data->progress.speeder_c++;

    /* figure out how many index entries of data we have stored in our speeder
       array. With N_ENTRIES filled in, we have about N_ENTRIES-1 seconds of
       transfer. Imagine, after one second we have filled in two entries,
       after two seconds we've filled in three entries etc. */
    countindex = ((data->progress.speeder_c >= CURR_TIME)?
                  CURR_TIME:data->progress.speeder_c) - 1;

    /* first of all, we don't do this if there's no counted seconds yet */
    if(countindex) {
      time_t span_ms;

      /* Get the index position to compare with the 'nowindex' position.
         Get the oldest entry possible. While we have less than CURR_TIME
         entries, the first entry will remain the oldest. */
      checkindex = (data->progress.speeder_c >= CURR_TIME)?
        data->progress.speeder_c%CURR_TIME:0;

      /* Figure out the exact time for the time span */
      span_ms = Curl_tvdiff(now,
                            data->progress.speeder_time[checkindex]);
      if(0 == span_ms)
        span_ms = 1; /* at least one millisecond MUST have passed */

      /* Calculate the average speed the last 'span_ms' milliseconds */
      {
        curl_off_t amount = data->progress.speeder[nowindex]-
          data->progress.speeder[checkindex];

        if(amount > CURL_OFF_T_C(4294967) /* 0xffffffff/1000 */)
          /* the 'amount' value is bigger than would fit in 32 bits if
             multiplied with 1000, so we use the double math for this */
          data->progress.current_speed = (curl_off_t)
            ((double)amount/((double)span_ms/1000.0));
        else
          /* the 'amount' value is small enough to fit within 32 bits even
             when multiplied with 1000 */
          data->progress.current_speed = amount*CURL_OFF_T_C(1000)/span_ms;
      }
    }
    else
      /* the first second we use the average */
      data->progress.current_speed =
        data->progress.ulspeed + data->progress.dlspeed;

  } /* Calculations end */

  if(!(data->progress.flags & PGRS_HIDE)) {
    /* progress meter has not been shut off */

    if(data->set.fxferinfo) {
      /* There's a callback set, call that */
      result = data->set.fxferinfo(data->set.progress_client,
                                   data->progress.size_dl,
                                   data->progress.downloaded,
                                   data->progress.size_ul,
                                   data->progress.uploaded);
      if(result)
        failf(data, "Callback aborted");
      return result;
    }
    if(data->set.fprogress) {
      /* The older deprecated callback is set, call that */
      result = data->set.fprogress(data->set.progress_client,
                                   (double)data->progress.size_dl,
                                   (double)data->progress.downloaded,
                                   (double)data->progress.size_ul,
                                   (double)data->progress.uploaded);
      if(result)
        failf(data, "Callback aborted");
      return result;
    }

    if(!shownow)
      /* only show the internal progress meter once per second */
      return 0;

    /* If there's no external callback set, use internal code to show
       progress */

    if(!(data->progress.flags & PGRS_HEADERS_OUT)) {
      if(data->state.resume_from) {
        fprintf(data->set.err,
                "** Resuming transfer from byte position %"
                CURL_FORMAT_CURL_OFF_T "\n", data->state.resume_from);
      }
      fprintf(data->set.err,
              "  %% Total    %% Received %% Xferd  Average Speed   "
              "Time    Time     Time  Current\n"
              "                                 Dload  Upload   "
              "Total   Spent    Left  Speed\n");
      data->progress.flags |= PGRS_HEADERS_OUT; /* headers are shown */
    }

    /* Figure out the estimated time of arrival for the upload */
    if((data->progress.flags & PGRS_UL_SIZE_KNOWN) &&
       (data->progress.ulspeed > CURL_OFF_T_C(0))) {
      ulestimate = data->progress.size_ul / data->progress.ulspeed;

      if(data->progress.size_ul > CURL_OFF_T_C(10000))
        ulpercen = data->progress.uploaded /
          (data->progress.size_ul/CURL_OFF_T_C(100));
      else if(data->progress.size_ul > CURL_OFF_T_C(0))
        ulpercen = (data->progress.uploaded*100) /
          data->progress.size_ul;
    }

    /* ... and the download */
    if((data->progress.flags & PGRS_DL_SIZE_KNOWN) &&
       (data->progress.dlspeed > CURL_OFF_T_C(0))) {
      dlestimate = data->progress.size_dl / data->progress.dlspeed;

      if(data->progress.size_dl > CURL_OFF_T_C(10000))
        dlpercen = data->progress.downloaded /
          (data->progress.size_dl/CURL_OFF_T_C(100));
      else if(data->progress.size_dl > CURL_OFF_T_C(0))
        dlpercen = (data->progress.downloaded*100) /
          data->progress.size_dl;
    }

    /* Now figure out which of them is slower and use that one for the
       total estimate! */
    total_estimate = ulestimate>dlestimate?ulestimate:dlestimate;

    /* create the three time strings */
    time2str(time_left, total_estimate > 0?(total_estimate - timespent):0);
    time2str(time_total, total_estimate);
    time2str(time_spent, timespent);

    /* Get the total amount of data expected to get transferred */
    total_expected_transfer =
      (data->progress.flags & PGRS_UL_SIZE_KNOWN?
       data->progress.size_ul:data->progress.uploaded)+
      (data->progress.flags & PGRS_DL_SIZE_KNOWN?
       data->progress.size_dl:data->progress.downloaded);

    /* We have transferred this much so far */
    total_transfer = data->progress.downloaded + data->progress.uploaded;

    /* Get the percentage of data transferred so far */
    if(total_expected_transfer > CURL_OFF_T_C(10000))
      total_percen = total_transfer /
        (total_expected_transfer/CURL_OFF_T_C(100));
    else if(total_expected_transfer > CURL_OFF_T_C(0))
      total_percen = (total_transfer*100) / total_expected_transfer;

    fprintf(data->set.err,
            "\r"
            "%3" CURL_FORMAT_CURL_OFF_T " %s  "
            "%3" CURL_FORMAT_CURL_OFF_T " %s  "
            "%3" CURL_FORMAT_CURL_OFF_T " %s  %s  %s %s %s %s %s",
            total_percen,  /* 3 letters */                /* total % */
            max5data(total_expected_transfer, max5[2]),   /* total size */
            dlpercen,      /* 3 letters */                /* rcvd % */
            max5data(data->progress.downloaded, max5[0]), /* rcvd size */
            ulpercen,      /* 3 letters */                /* xfer % */
            max5data(data->progress.uploaded, max5[1]),   /* xfer size */
            max5data(data->progress.dlspeed, max5[3]),    /* avrg dl speed */
            max5data(data->progress.ulspeed, max5[4]),    /* avrg ul speed */
            time_total,    /* 8 letters */                /* total time */
            time_spent,    /* 8 letters */                /* time spent */
            time_left,     /* 8 letters */                /* time left */
            max5data(data->progress.current_speed, max5[5]) /* current speed */
            );

    /* we flush the output stream to make it appear as soon as possible */
    fflush(data->set.err);

  } /* !(data->progress.flags & PGRS_HIDE) */

  return 0;
}