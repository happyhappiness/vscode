static int conn_init(void) {
  char buf[_POSIX2_LINE_MAX];

  kvmd = kvm_openfiles(NULL, NULL, NULL, KVM_NO_FILES, buf);
  if (kvmd == NULL) {
    ERROR("tcpconns plugin: kvm_openfiles failed: %s", buf);
    return -1;
  }

  return 0;
}