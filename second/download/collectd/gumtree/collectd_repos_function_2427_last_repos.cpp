void module_register(void) {
  target_proc_t tproc = {0};

  tproc.create = ts_create;
  tproc.destroy = ts_destroy;
  tproc.invoke = ts_invoke;
  fc_register_target("scale", tproc);
}