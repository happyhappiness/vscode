static CURLcode ssh_check_fingerprint(struct connectdata *conn)
{
  struct ssh_conn *sshc = &conn->proto.sshc;
  struct SessionHandle *data = conn->data;
  const char *pubkey_md5 = data->set.str[STRING_SSH_HOST_PUBLIC_KEY_MD5];
  char md5buffer[33];
  int i;

  const char *fingerprint = libssh2_hostkey_hash(sshc->ssh_session,
      LIBSSH2_HOSTKEY_HASH_MD5);

  if(fingerprint) {
    /* The fingerprint points to static storage (!), don't free() it. */
    for(i = 0; i < 16; i++)
      snprintf(&md5buffer[i*2], 3, "%02x", (unsigned char) fingerprint[i]);
    infof(data, "SSH MD5 fingerprint: %s\n", md5buffer);
  }

  /* Before we authenticate we check the hostkey's MD5 fingerprint
   * against a known fingerprint, if available.
   */
  if(pubkey_md5 && strlen(pubkey_md5) == 32) {
    if(!fingerprint || !strequal(md5buffer, pubkey_md5)) {
      if(fingerprint)
        failf(data,
            "Denied establishing ssh session: mismatch md5 fingerprint. "
            "Remote %s is not equal to %s", md5buffer, pubkey_md5);
      else
        failf(data,
            "Denied establishing ssh session: md5 fingerprint not available");
      state(conn, SSH_SESSION_FREE);
      sshc->actualcode = CURLE_PEER_FAILED_VERIFICATION;
      return sshc->actualcode;
    }
    else {
      infof(data, "MD5 checksum match!\n");
      /* as we already matched, we skip the check for known hosts */
      return CURLE_OK;
    }
  }
  else
    return ssh_knownhost(conn);
}