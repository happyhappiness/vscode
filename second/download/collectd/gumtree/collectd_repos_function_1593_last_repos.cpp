static int as_init(void) {
  kern_return_t status;

  if (io_master_port != MACH_PORT_NULL) {
    mach_port_deallocate(mach_task_self(), io_master_port);
    io_master_port = MACH_PORT_NULL;
  }

  status = IOMasterPort(MACH_PORT_NULL, &io_master_port);
  if (status != kIOReturnSuccess) {
    ERROR("IOMasterPort failed: %s", mach_error_string(status));
    io_master_port = MACH_PORT_NULL;
    return -1;
  }

  return 0;
}