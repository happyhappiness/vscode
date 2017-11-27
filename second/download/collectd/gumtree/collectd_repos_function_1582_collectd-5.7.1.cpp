void module_register(void) {
  match_proc_t mproc = {0};

  mproc.create = mt_create;
  mproc.destroy = mt_destroy;
  mproc.match = mt_match;
  fc_register_match("timediff", mproc);
}