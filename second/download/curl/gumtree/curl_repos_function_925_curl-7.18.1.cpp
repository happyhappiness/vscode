static int
sec_send(struct connectdata *conn, int fd, char *from, int length)
{
  int bytes;
  void *buf;
  enum protection_level protlevel = conn->data_prot;
  int iscmd = protlevel == prot_cmd;

  if(iscmd) {
    if(!strncmp(from, "PASS ", 5) || !strncmp(from, "ACCT ", 5))
      protlevel = prot_private;
    else
      protlevel = conn->command_prot;
  }
  bytes = (conn->mech->encode)(conn->app_data, from, length, protlevel,
                               &buf, conn);
  if(iscmd) {
    char *cmdbuf;

    bytes = Curl_base64_encode(conn->data, (char *)buf, bytes, &cmdbuf);
    if(bytes > 0) {
      if(protlevel == prot_private)
        block_write(fd, "ENC ", 4);
      else
        block_write(fd, "MIC ", 4);
      block_write(fd, cmdbuf, bytes);
      block_write(fd, "\r\n", 2);
      Curl_infof(conn->data, "%s %s\n",
                 protlevel == prot_private ? "ENC" : "MIC", cmdbuf);
      free(cmdbuf);
    }
  }
  else {
    bytes = htonl(bytes);
    block_write(fd, &bytes, sizeof(bytes));
    block_write(fd, buf, ntohl(bytes));
  }
  free(buf);
  return length;
}