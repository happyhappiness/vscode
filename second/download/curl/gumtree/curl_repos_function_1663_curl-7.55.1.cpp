static CURLcode pop3_perform_command(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  const char *command = NULL;

  /* Calculate the default command */
  if(pop3->id[0] == '\0' || conn->data->set.ftp_list_only) {
    command = "LIST";

    if(pop3->id[0] != '\0')
      /* Message specific LIST so skip the BODY transfer */
      pop3->transfer = FTPTRANSFER_INFO;
  }
  else
    command = "RETR";

  /* Send the command */
  if(pop3->id[0] != '\0')
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s %s",
                           (pop3->custom && pop3->custom[0] != '\0' ?
                            pop3->custom : command), pop3->id);
  else
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s",
                           (pop3->custom && pop3->custom[0] != '\0' ?
                            pop3->custom : command));

  if(!result)
    state(conn, POP3_COMMAND);

  return result;
}