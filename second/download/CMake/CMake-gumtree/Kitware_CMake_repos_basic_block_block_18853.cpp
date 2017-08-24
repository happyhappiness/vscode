{
    vm_deallocate(mach_task_self(), (vm_address_t)info, msg_type);
    return -ENOMEM;
  }