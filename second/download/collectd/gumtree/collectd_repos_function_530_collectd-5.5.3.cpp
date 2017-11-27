void module_register (void) /* {{{ */
{
#ifdef KERNEL_LINUX
  plugin_register_init ("ipc", ipc_init);
#endif
  plugin_register_read ("ipc", ipc_read);
}