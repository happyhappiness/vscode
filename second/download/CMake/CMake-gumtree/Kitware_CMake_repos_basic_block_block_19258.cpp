{
  struct kinfo_proc kinfo;
  size_t page_size = getpagesize();
  size_t size = sizeof(struct kinfo_proc);
  int mib[6];

  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC;
  mib[2] = KERN_PROC_PID;
  mib[3] = getpid();
  mib[4] = sizeof(struct kinfo_proc);
  mib[5] = 1;

  if (sysctl(mib, 6, &kinfo, &size, NULL, 0) < 0)
    return -errno;

  *rss = kinfo.p_vm_rssize * page_size;
  return 0;
}