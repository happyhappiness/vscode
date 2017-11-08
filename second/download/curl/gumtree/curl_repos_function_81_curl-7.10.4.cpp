int myprogress (void *clientp,
                double dltotal,
                double dlnow,
                double ultotal,
                double ulnow)
{
  /* The original progress-bar source code was written for curl by Lars Aas,
     and this new edition inherites some of his concepts. */
  
  char line[256];
  char outline[256];
  char format[40];
  double frac;
  double percent;
  int barwidth;
  int num;
  int i;

  struct ProgressData *bar = (struct ProgressData *)clientp;
  double total = dltotal + ultotal;

  bar->point = dlnow + ulnow; /* we've come this far */

  bar->calls++; /* simply count invokes */

  if(0 == total) {
    int prevblock = (int)bar->prev / 1024;
    int thisblock = (int)bar->point / 1024;
    while ( thisblock > prevblock ) {
      fprintf( bar->out, "#" );
      prevblock++;
    }
  }
  else {
    frac = bar->point / total;
    percent = frac * 100.0f;
    barwidth = bar->width - 7;
    num = (int) (((double)barwidth) * frac);
    i = 0;
    for ( i = 0; i < num; i++ ) {
      line[i] = '#';
    }
    line[i] = '\0';
    sprintf( format, "%%-%ds %%5.1f%%%%", barwidth );
    sprintf( outline, format, line, percent );
    fprintf( bar->out, "\r%s", outline );
  }
  bar->prev = bar->point;

  return 0;
}