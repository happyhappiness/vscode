static int init(void) {
#if PROCESSOR_CPU_LOAD_INFO
  kern_return_t status;

  port_host = mach_host_self();

  status = host_processors(port_host, &cpu_list, &cpu_list_len);
  if (status == KERN_INVALID_ARGUMENT) {
    ERROR("cpu plugin: Don't have a privileged host control port. "
          "The most common cause for this problem is "
          "that collectd is running without root "
          "privileges, which are required to read CPU "
          "load information. "
          "<https://collectd.org/bugs/22>");
    cpu_list_len = 0;
    return -1;
  }
  if (status != KERN_SUCCESS) {
    ERROR("cpu plugin: host_processors() failed with status %d.", (int)status);
    cpu_list_len = 0;
    return -1;
  }

  INFO("cpu plugin: Found %i processor%s.", (int)cpu_list_len,
       cpu_list_len == 1 ? "" : "s");
/* #endif PROCESSOR_CPU_LOAD_INFO */

#elif defined(HAVE_LIBKSTAT)
  kstat_t *ksp_chain;

  numcpu = 0;

  if (kc == NULL)
    return -1;

  /* Solaris doesn't count linear.. *sigh* */
  for (numcpu = 0, ksp_chain = kc->kc_chain;
       (numcpu < MAX_NUMCPU) && (ksp_chain != NULL);
       ksp_chain = ksp_chain->ks_next)
    if (strncmp(ksp_chain->ks_module, "cpu_stat", 8) == 0)
      ksp[numcpu++] = ksp_chain;
/* #endif HAVE_LIBKSTAT */

#elif CAN_USE_SYSCTL
  size_t numcpu_size;
  int mib[2] = {CTL_HW, HW_NCPU};
  int status;

  numcpu = 0;
  numcpu_size = sizeof(numcpu);

  status = sysctl(mib, STATIC_ARRAY_SIZE(mib), &numcpu, &numcpu_size, NULL, 0);
  if (status == -1) {
    char errbuf[1024];
    WARNING("cpu plugin: sysctl: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }
/* #endif CAN_USE_SYSCTL */

#elif defined(HAVE_SYSCTLBYNAME)
  size_t numcpu_size;

  numcpu_size = sizeof(numcpu);

  if (sysctlbyname("hw.ncpu", &numcpu, &numcpu_size, NULL, 0) < 0) {
    char errbuf[1024];
    WARNING("cpu plugin: sysctlbyname(hw.ncpu): %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

#ifdef HAVE_SYSCTL_KERN_CP_TIMES
  numcpu_size = sizeof(maxcpu);

  if (sysctlbyname("kern.smp.maxcpus", &maxcpu, &numcpu_size, NULL, 0) < 0) {
    char errbuf[1024];
    WARNING("cpu plugin: sysctlbyname(kern.smp.maxcpus): %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }
#else
  if (numcpu != 1)
    NOTICE("cpu: Only one processor supported when using `sysctlbyname' (found "
           "%i)",
           numcpu);
#endif
/* #endif HAVE_SYSCTLBYNAME */

#elif defined(HAVE_LIBSTATGRAB)
/* nothing to initialize */
/* #endif HAVE_LIBSTATGRAB */

#elif defined(HAVE_PERFSTAT)
/* nothing to initialize */
#endif /* HAVE_PERFSTAT */

  return 0;
}