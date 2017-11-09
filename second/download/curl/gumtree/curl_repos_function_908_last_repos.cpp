int tool_progress_cb(void *clientp,
                     curl_off_t dltotal, curl_off_t dlnow,
                     curl_off_t ultotal, curl_off_t ulnow)
{
  /* The original progress-bar source code was written for curl by Lars Aas,
     and this new edition inherits some of his concepts. */

  char line[MAX_BARLENGTH + 1];
  char format[40];
  double frac;
  double percent;
  int barwidth;
  int num;
  struct timeval now = tvnow();
  struct ProgressData *bar = (struct ProgressData *)clientp;
  curl_off_t total;
  curl_off_t point;

  /* expected transfer size */
  total = dltotal + ultotal + bar->initial_size;

  /* we've come this far */
  point = dlnow + ulnow + bar->initial_size;

  if(bar->calls && (tvdiff(now, bar->prevtime) < 100L) && point < total)
    /* after first call, limit progress-bar updating to 10 Hz */
    /* update when we're at 100% even if last update is less than 200ms ago */
    return 0;

  if(point > total)
    /* we have got more than the expected total! */
    total = point;

  /* simply count invokes */
  bar->calls++;

  if(total < 1) {
    curl_off_t prevblock = bar->prev / 1024;
    curl_off_t thisblock = point / 1024;
    while(thisblock > prevblock) {
      fprintf(bar->out, "#");
      prevblock++;
    }
  }
  else if(point != bar->prev) {
    frac = (double)point / (double)total;
    percent = frac * 100.0;
    barwidth = bar->width - 7;
    num = (int) (((double)barwidth) * frac);
    if(num > MAX_BARLENGTH)
      num = MAX_BARLENGTH;
    memset(line, '#', num);
    line[num] = '\0';
    snprintf(format, sizeof(format), "\r%%-%ds %%5.1f%%%%", barwidth);
    fprintf(bar->out, format, line, percent);
  }
  fflush(bar->out);
  bar->prev = point;
  bar->prevtime = now;

  return 0;
}