static int fc_init_once(void) /* {{{ */
{
  static int done = 0;
  target_proc_t tproc = {0};

  if (done != 0)
    return 0;

  tproc.create = fc_bit_jump_create;
  tproc.destroy = fc_bit_jump_destroy;
  tproc.invoke = fc_bit_jump_invoke;
  fc_register_target("jump", tproc);

  memset(&tproc, 0, sizeof(tproc));
  tproc.create = NULL;
  tproc.destroy = NULL;
  tproc.invoke = fc_bit_stop_invoke;
  fc_register_target("stop", tproc);

  memset(&tproc, 0, sizeof(tproc));
  tproc.create = NULL;
  tproc.destroy = NULL;
  tproc.invoke = fc_bit_return_invoke;
  fc_register_target("return", tproc);

  memset(&tproc, 0, sizeof(tproc));
  tproc.create = fc_bit_write_create;
  tproc.destroy = fc_bit_write_destroy;
  tproc.invoke = fc_bit_write_invoke;
  fc_register_target("write", tproc);

  done++;
  return 0;
}