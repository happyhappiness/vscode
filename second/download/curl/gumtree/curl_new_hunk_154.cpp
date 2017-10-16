 */
static void main_free(void)
{
  curl_global_cleanup();
}

static int SetHTTPrequest(struct Configurable *config,
                          HttpReq req, HttpReq *store)
{
  if((*store == HTTPREQ_UNSPEC) ||
     (*store == req)) {
    *store = req;
    return 0;
  }
  warnf(config, "You can only select one HTTP request!\n");
  return 1;
}

static void helpf(const char *fmt, ...)
{
  va_list ap;
