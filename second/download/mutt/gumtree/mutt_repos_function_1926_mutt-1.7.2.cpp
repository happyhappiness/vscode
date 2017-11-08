imap_auth_res_t imap_auth_gss (IMAP_DATA* idata, const char* method)
{
  gss_buffer_desc request_buf, send_token;
  gss_buffer_t sec_token;
  gss_name_t target_name;
  gss_ctx_id_t context;
#ifdef DEBUG
  gss_OID mech_name;
  char server_conf_flags;
#endif
  gss_qop_t quality;
  int cflags;
  OM_uint32 maj_stat, min_stat;
  char buf1[GSS_BUFSIZE], buf2[GSS_BUFSIZE];
  unsigned long buf_size;
  int rc;

  if (!mutt_bit_isset (idata->capabilities, AGSSAPI))
    return IMAP_AUTH_UNAVAIL;

  if (mutt_account_getuser (&idata->conn->account))
    return IMAP_AUTH_FAILURE;
  
  /* get an IMAP service ticket for the server */
  snprintf (buf1, sizeof (buf1), "imap@%s", idata->conn->account.host);
  request_buf.value = buf1;
  request_buf.length = strlen (buf1) + 1;
  maj_stat = gss_import_name (&min_stat, &request_buf, gss_nt_service_name,
    &target_name);
  if (maj_stat != GSS_S_COMPLETE)
  {
    dprint (2, (debugfile, "Couldn't get service name for [%s]\n", buf1));
    return IMAP_AUTH_UNAVAIL;
  }
#ifdef DEBUG	
  else if (debuglevel >= 2)
  {
    maj_stat = gss_display_name (&min_stat, target_name, &request_buf,
      &mech_name);
    dprint (2, (debugfile, "Using service name [%s]\n",
      (char*) request_buf.value));
    maj_stat = gss_release_buffer (&min_stat, &request_buf);
  }
#endif
  /* Acquire initial credentials - without a TGT GSSAPI is UNAVAIL */
  sec_token = GSS_C_NO_BUFFER;
  context = GSS_C_NO_CONTEXT;

  /* build token */
  maj_stat = gss_init_sec_context (&min_stat, GSS_C_NO_CREDENTIAL, &context,
    target_name, GSS_C_NO_OID, GSS_C_MUTUAL_FLAG | GSS_C_SEQUENCE_FLAG, 0, 
    GSS_C_NO_CHANNEL_BINDINGS, sec_token, NULL, &send_token,
    (unsigned int*) &cflags, NULL);
  if (maj_stat != GSS_S_COMPLETE && maj_stat != GSS_S_CONTINUE_NEEDED)
  {
    print_gss_error(maj_stat, min_stat);
    dprint (1, (debugfile, "Error acquiring credentials - no TGT?\n"));
    gss_release_name (&min_stat, &target_name);

    return IMAP_AUTH_UNAVAIL;
  }

  /* now begin login */
  mutt_message _("Authenticating (GSSAPI)...");

  imap_cmd_start (idata, "AUTHENTICATE GSSAPI");

  /* expect a null continuation response ("+") */
  do
    rc = imap_cmd_step (idata);
  while (rc == IMAP_CMD_CONTINUE);

  if (rc != IMAP_CMD_RESPOND)
  {
    dprint (2, (debugfile, "Invalid response from server: %s\n", buf1));
    gss_release_name (&min_stat, &target_name);
    goto bail;
  }

  /* now start the security context initialisation loop... */
  dprint (2, (debugfile, "Sending credentials\n"));
  mutt_to_base64 ((unsigned char*) buf1, send_token.value, send_token.length,
    sizeof (buf1) - 2);
  gss_release_buffer (&min_stat, &send_token);
  safe_strcat (buf1, sizeof (buf1), "\r\n");
  mutt_socket_write (idata->conn, buf1);

  while (maj_stat == GSS_S_CONTINUE_NEEDED)
  {
    /* Read server data */
    do
      rc = imap_cmd_step (idata);
    while (rc == IMAP_CMD_CONTINUE);

    if (rc != IMAP_CMD_RESPOND)
    {
      dprint (1, (debugfile, "Error receiving server response.\n"));
      gss_release_name (&min_stat, &target_name);
      goto bail;
    }

    request_buf.length = mutt_from_base64 (buf2, idata->buf + 2);
    request_buf.value = buf2;
    sec_token = &request_buf;

    /* Write client data */
    maj_stat = gss_init_sec_context (&min_stat, GSS_C_NO_CREDENTIAL, &context,
      target_name, GSS_C_NO_OID, GSS_C_MUTUAL_FLAG | GSS_C_SEQUENCE_FLAG, 0, 
      GSS_C_NO_CHANNEL_BINDINGS, sec_token, NULL, &send_token,
      (unsigned int*) &cflags, NULL);
    if (maj_stat != GSS_S_COMPLETE && maj_stat != GSS_S_CONTINUE_NEEDED)
    {
      print_gss_error(maj_stat, min_stat);
      dprint (1, (debugfile, "Error exchanging credentials\n"));
      gss_release_name (&min_stat, &target_name);

      goto err_abort_cmd;
    }
    mutt_to_base64 ((unsigned char*) buf1, send_token.value,
      send_token.length, sizeof (buf1) - 2);
    gss_release_buffer (&min_stat, &send_token);
    safe_strcat (buf1, sizeof (buf1), "\r\n");
    mutt_socket_write (idata->conn, buf1);
  }

  gss_release_name (&min_stat, &target_name);

  /* get security flags and