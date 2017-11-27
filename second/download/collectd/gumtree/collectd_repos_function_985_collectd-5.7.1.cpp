static int conn_init(void) {
  char buf[_POSIX2_LINE_MAX];
  struct nlist nl[] = {
#define N_TCBTABLE 0
      {"_tcbtable"}, {""}};
  int status;

  kvmd = kvm_openfiles(NULL, NULL, NULL, O_RDONLY, buf);
  if (kvmd == NULL) {
    ERROR("tcpconns plugin: kvm_openfiles failed: %s", buf);
    return (-1);
  }

  status = kvm_nlist(kvmd, nl);
  if (status < 0) {
    ERROR("tcpconns plugin: kvm_nlist failed with status %i.", status);
    return (-1);
  }

  if (nl[N_TCBTABLE].n_type == 0) {
    ERROR("tcpconns plugin: Error looking up kernel's namelist: "
          "N_TCBTABLE is invalid.");
    return (-1);
  }

  inpcbtable_off = (u_long)nl[N_TCBTABLE].n_value;
  inpcbtable_ptr = (struct inpcbtable *)nl[N_TCBTABLE].n_value;

  return (0);
}