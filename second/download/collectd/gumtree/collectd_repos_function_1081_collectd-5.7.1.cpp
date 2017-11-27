void module_register(void) {
  target_proc_t tproc = {0};

  tproc.create = tn_create;
  tproc.destroy = tn_destroy;
  tproc.invoke = tn_invoke;
  fc_register_target("notification", tproc);
}