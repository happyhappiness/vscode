static int tss2_read(void) {
  /*
   * Poll function which collects global and vserver information
   * and submits it to collectd
   */
  int success = 0;
  int status;

  /* Handle global server variables */
  status = tss2_read_vserver(NULL);
  if (status == 0) {
    success++;
  } else {
    WARNING("teamspeak2 plugin: Reading global server variables failed.");
  }

  /* Handle vservers */
  for (vserver_list_t *vserver = server_list; vserver != NULL;
       vserver = vserver->next) {
    status = tss2_read_vserver(vserver);
    if (status == 0) {
      success++;
    } else {
      WARNING("teamspeak2 plugin: Reading statistics "
              "for vserver %i failed.",
              vserver->port);
      continue;
    }
  }

  if (success == 0)
    return (-1);
  return (0);
}