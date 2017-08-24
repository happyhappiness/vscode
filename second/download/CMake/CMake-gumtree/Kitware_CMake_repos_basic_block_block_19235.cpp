{
  kvm_t *kd = NULL;
  struct kinfo_proc2 *kinfo = NULL;
  pid_t pid;
  int nprocs;
  int max_size = sizeof(struct kinfo_proc2);
  int page_size;

  page_size = getpagesize();
  pid = getpid();

  kd = kvm_open(NULL, NULL, NULL, KVM_NO_FILES, "kvm_open");

  if (kd == NULL) goto error;

  kinfo = kvm_getproc2(kd, KERN_PROC_PID, pid, max_size, &nprocs);
  if (kinfo == NULL) goto error;

  *rss = kinfo->p_vm_rssize * page_size;

  kvm_close(kd);

  return 0;

error:
  if (kd) kvm_close(kd);
  return -EPERM;
}