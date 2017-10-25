int myprogress (void *clientp,
                size_t dltotal,
                size_t dlnow,
                size_t ultotal,
                size_t ulnow)
{
  /* The original progress-bar source code was written for curl by Lars Aas,
     and this new edition inherites some of his concepts. */
  
  char line[256];
  char outline[256];
  char format[40];
  float frac;
  float percent;
  int barwidth;
  int num;
  int i;
  int prevblock;
  int thisblock;

  struct ProgressData *bar = (struct ProgressData *)clientp;
  size_t total = dltotal + ultotal;

  bar->point = dlnow + ulnow; /* we've come this far */

  if(0 == total) {
    int prevblock = bar->prev / 1024;
    int thisblock = bar->point / 1024;
    while ( thisblock > prevblock ) {
      fprintf( stderr, "#" );
      prevblock++;
    }
  }
  else {
    frac = (float) bar->point / (float) total;
    percent = frac * 100.0f;
    barwidth = bar->width - 7;
    num = (int) (((float)barwidth) * frac);
    i = 0;
    for ( i = 0; i < num; i++ ) {
      line[i] = '#';
    }
    line[i] = '\0';
    sprintf( format, "%%-%ds %%5.1f%%%%", barwidth );
    sprintf( outline, format, line, percent );
    fprintf( stderr, "\r%s", outline );
  }
  bar->prev = bar->point;

  return 0;
}