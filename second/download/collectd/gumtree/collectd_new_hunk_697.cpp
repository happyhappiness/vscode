{
  struct timespec ts = {0};

  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
    perror("clock_gettime");

  return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
} /* }}} double dtime */
#else
/* Work around for Mac OS X which doesn't have clock_gettime(2). *sigh* */
static double dtime(void) /* {{{ */
{
  struct timeval tv = {0};

  if (gettimeofday(&tv, /* timezone = */ NULL) != 0)
    perror("gettimeofday");

  return (double)tv.tv_sec + ((double)tv.tv_usec) / 1e6;
} /* }}} double dtime */
#endif

static int compare_time(const void *v0, const void *v1) /* {{{ */
{
  const lcc_value_list_t *vl0 = v0;
  const lcc_value_list_t *vl1 = v1;

  if (vl0->time < vl1->time)
    return -1;
  else if (vl0->time > vl1->time)
    return 1;
  else
    return 0;
} /* }}} int compare_time */

static int get_boundet_random(int min, int max) /* {{{ */
{
  int range;

  if (min >= max)
    return -1;
  if (min == (max - 1))
    return min;

  range = max - min;

  return min + ((int)(((double)range) * ((double)random()) / (((double)RAND_MAX) + 1.0)));
} /* }}} int get_boundet_random */

static lcc_value_list_t *create_value_list(void) /* {{{ */
{
  lcc_value_list_t *vl;
  int host_num;

  vl = calloc(1, sizeof(*vl));
  if (vl == NULL) {
    fprintf(stderr, "calloc failed.\n");
    return NULL;
  }

  vl->values = calloc(/* nmemb = */ 1, sizeof(*vl->values));
  if (vl->values == NULL) {
    fprintf(stderr, "calloc failed.\n");
    free(vl);
    return NULL;
  }

  vl->values_types = calloc(/* nmemb = */ 1, sizeof(*vl->values_types));
  if (vl->values_types == NULL) {
    fprintf(stderr, "calloc failed.\n");
    free(vl->values);
    free(vl);
    return NULL;
  }

  vl->values_len = 1;

  host_num = get_boundet_random(0, conf_num_hosts);

