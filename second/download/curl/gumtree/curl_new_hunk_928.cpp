{
  if((*store == HTTPREQ_UNSPEC) ||
     (*store == req)) {
    *store = req;
    return 0;
  }

  warnf(config->global, "You can only select one HTTP request!\n");

  return 1;
}
