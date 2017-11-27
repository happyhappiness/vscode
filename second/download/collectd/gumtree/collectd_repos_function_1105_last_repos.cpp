static int multi2_read(const char *name, FILE *fh) {
  char buffer[1024];
  /* OpenVPN-2.4 has 11 fields of data + 2 fields for "HEADER" and "CLIENT_LIST"
   * So, set array size to 20 elements, to support future extensions.
   */
  char *fields[20];
  const int max_fields = STATIC_ARRAY_SIZE(fields);
  long long sum_users = 0;

  _Bool found_header = 0;
  int idx_cname = 0;
  int idx_bytes_recv = 0;
  int idx_bytes_sent = 0;
  int columns = 0;

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    int fields_num = openvpn_strsplit(buffer, fields, max_fields);

    /* Try to find section header */
    if (found_header == 0) {
      if (fields_num < 2)
        continue;
      if (strcmp(fields[0], "HEADER") != 0)
        continue;
      if (strcmp(fields[1], "CLIENT_LIST") != 0)
        continue;

      for (int i = 2; i < fields_num; i++) {
        if (strcmp(fields[i], "Common Name") == 0) {
          idx_cname = i - 1;
        } else if (strcmp(fields[i], "Bytes Received") == 0) {
          idx_bytes_recv = i - 1;
        } else if (strcmp(fields[i], "Bytes Sent") == 0) {
          idx_bytes_sent = i - 1;
        }
      }

      DEBUG("openvpn plugin: found MULTI v2/v3 HEADER. "
            "Column idx: cname: %d, bytes_recv: %d, bytes_sent: %d",
            idx_cname, idx_bytes_recv, idx_bytes_sent);

      if (idx_cname == 0 || idx_bytes_recv == 0 || idx_bytes_sent == 0)
        break;

      /* Data row has 1 field ("HEADER") less than header row */
      columns = fields_num - 1;

      found_header = 1;
      continue;
    }

    /* Header already found. Check if the line is the section data.
     * If no match, then section was finished and there is no more data.
     * Empty section is OK too.
     */
    if (fields_num == 0 || strcmp(fields[0], "CLIENT_LIST") != 0)
      break;

    /* Check if the data line fields count matches header line. */
    if (fields_num != columns) {
      ERROR("openvpn plugin: File format error in instance %s: Fields count "
            "mismatch.",
            name);
      return -1;
    }

    DEBUG("openvpn plugin: found MULTI v2/v3 CLIENT_LIST. "
          "Columns: cname: %s, bytes_recv: %s, bytes_sent: %s",
          fields[idx_cname], fields[idx_bytes_recv], fields[idx_bytes_sent]);

    if (collect_user_count)
      sum_users += 1;

    if (collect_individual_users) {
      if (new_naming_schema) {
        /* plugin inst = file name, type inst = fields[1] */
        iostats_submit(name,                           /* vpn instance     */
                       fields[idx_cname],              /* "Common Name"    */
                       atoll(fields[idx_bytes_recv]),  /* "Bytes Received" */
                       atoll(fields[idx_bytes_sent])); /* "Bytes Sent"     */
      } else {
        /* plugin inst = fields[idx_cname], type inst = "" */
        iostats_submit(fields[idx_cname], /*              "Common Name"    */
                       NULL,              /* unused when in multimode      */
                       atoll(fields[idx_bytes_recv]),  /* "Bytes Received" */
                       atoll(fields[idx_bytes_sent])); /* "Bytes Sent"     */
      }
    }
  }

  if (ferror(fh))
    return -1;

  if (found_header == 0) {
    NOTICE("openvpn plugin: Unknown file format in instance %s, please "
           "report this as bug. Make sure to include "
           "your status file, so the plugin can "
           "be adapted.",
           name);
    return -1;
  }

  if (collect_user_count) {
    numusers_submit(name, name, sum_users);
  }

  return 0;
}