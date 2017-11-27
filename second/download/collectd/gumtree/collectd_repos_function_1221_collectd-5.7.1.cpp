void module_register(void) {
  target_proc_t tproc = {0};

  tproc.create = v5_create;
  tproc.destroy = v5_destroy;
  tproc.invoke = v5_invoke;
  fc_register_target("v5upgrade", tproc);
}