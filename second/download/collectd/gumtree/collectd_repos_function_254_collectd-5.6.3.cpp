void module_register(void) {
  match_proc_t mproc = {0};

  mproc.create = mh_create;
  mproc.destroy = mh_destroy;
  mproc.match = mh_match;
  fc_register_match("hashed", mproc);
}