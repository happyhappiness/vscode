{
  vm_statistics_data_t info;
  mach_msg_type_number_t count = sizeof(info) / sizeof(integer_t);

  if (host_statistics(mach_host_self(), HOST_VM_INFO,
                      (host_info_t)&info, &count) != KERN_SUCCESS) {
    return -EINVAL;  /* FIXME(bnoordhuis) Translate error. */
  }

  return (uint64_t) info.free_count * sysconf(_SC_PAGESIZE);
}