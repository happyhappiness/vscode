static CURLcode ftp_state_prepare_transfer(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->data->req.protop;
  struct Curl_easy *data = conn->data;

  if(ftp->transfer != FTPTRANSFER_BODY) {
    /* doesn't transfer any data */

    /* still possibly do PRE QUOTE jobs */
    state(conn, FTP_RETR_PREQUOTE);
    result = ftp_state_quote(conn, TRUE, FTP_RETR_PREQUOTE);
  }
  else if(data->set.ftp_use_port) {
    /* We have chosen to use the PORT (or similar) command */
    result = ftp_state_use_port(conn, EPRT);
  }
  else {
    /* We have chosen (this is default) to use the PASV (or similar) command */
    if(data->set.ftp_use_pret) {
      /* The user has requested that we send a PRET command
         to prepare the server for the upcoming PASV */
      if(!conn->proto.ftpc.file) {
        PPSENDF(&conn->proto.ftpc.pp, "PRET %s",
                data->set.str[STRING_CUSTOMREQUEST]?
                data->set.str[STRING_CUSTOMREQUEST]:
                (data->set.ftp_list_only?"NLST":"LIST"));
      }
      else if(data->set.upload) {
        PPSENDF(&conn->proto.ftpc.pp, "PRET STOR %s", conn->proto.ftpc.file);
      }
      else {
        PPSENDF(&conn->proto.ftpc.pp, "PRET RETR %s", conn->proto.ftpc.file);
      }
      state(conn, FTP_PRET);
    }
    else {
      result = ftp_state_use_pasv(conn);
    }
  }
  return result;
}