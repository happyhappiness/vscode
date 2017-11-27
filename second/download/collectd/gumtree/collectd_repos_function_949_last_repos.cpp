static int conn_read(void) {
  struct kinfo_file *kf;
  int i, fcnt;

  conn_reset_port_entry();

  kf = kvm_getfiles(kvmd, KERN_FILE_BYFILE, DTYPE_SOCKET, sizeof(*kf), &fcnt);
  if (kf == NULL) {
    ERROR("tcpconns plugin: kvm_getfiles failed.");
    return -1;
  }

  for (i = 0; i < fcnt; i++) {
    if (kf[i].so_protocol != IPPROTO_TCP)
      continue;
    if (kf[i].inp_fport == 0)
      continue;
    conn_handle_ports(ntohs(kf[i].inp_lport), ntohs(kf[i].inp_fport),
                      kf[i].t_state);
  }

  conn_submit_all();

  return 0;
}