static int load_read(void) {
#if defined(HAVE_GETLOADAVG)
  double load[3];

  if (getloadavg(load, 3) == 3)
    load_submit(load[LOADAVG_1MIN], load[LOADAVG_5MIN], load[LOADAVG_15MIN]);
  else {
    char errbuf[1024];
    WARNING("load: getloadavg failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
  }
/* #endif HAVE_GETLOADAVG */

#elif defined(KERNEL_LINUX)
  gauge_t snum, mnum, lnum;
  FILE *loadavg;
  char buffer[16];

  char *fields[8];
  int numfields;

  if ((loadavg = fopen("/proc/loadavg", "r")) == NULL) {
    char errbuf[1024];
    WARNING("load: fopen: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  if (fgets(buffer, 16, loadavg) == NULL) {
    char errbuf[1024];
    WARNING("load: fgets: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
    fclose(loadavg);
    return -1;
  }

  if (fclose(loadavg)) {
    char errbuf[1024];
    WARNING("load: fclose: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
  }

  numfields = strsplit(buffer, fields, 8);

  if (numfields < 3)
    return -1;

  snum = atof(fields[0]);
  mnum = atof(fields[1]);
  lnum = atof(fields[2]);

  load_submit(snum, mnum, lnum);
/* #endif KERNEL_LINUX */

#elif HAVE_LIBSTATGRAB
  gauge_t snum, mnum, lnum;
  sg_load_stats *ls;

  if ((ls = sg_get_load_stats()) == NULL)
    return;

  snum = ls->min1;
  mnum = ls->min5;
  lnum = ls->min15;
  load_submit(snum, mnum, lnum);
/* #endif HAVE_LIBSTATGRAB */

#elif HAVE_PERFSTAT
  gauge_t snum, mnum, lnum;
  perfstat_cpu_total_t cputotal;

  if (perfstat_cpu_total(NULL, &cputotal, sizeof(perfstat_cpu_total_t), 1) <
      0) {
    char errbuf[1024];
    WARNING("load: perfstat_cpu : %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  snum = (float)cputotal.loadavg[0] / (float)(1 << SBITS);
  mnum = (float)cputotal.loadavg[1] / (float)(1 << SBITS);
  lnum = (float)cputotal.loadavg[2] / (float)(1 << SBITS);
  load_submit(snum, mnum, lnum);
/* #endif HAVE_PERFSTAT */

#else
#error "No applicable input method."
#endif

  return 0;
}