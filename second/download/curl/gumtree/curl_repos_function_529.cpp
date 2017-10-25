static CURLcode ftp_state_post_listtype(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  /* If this output is to be machine-parsed, the NLST command might be better
     to use, since the LIST command output is not specified or standard in any
     way. It has turned out that the NLST list output is not the same on all
     servers either... */

  NBFTPSENDF(conn, "%s",
             data->set.customrequest?data->set.customrequest:
             (data->set.ftp_list_only?"NLST":"LIST"));

  state(conn, FTP_LIST);

  return result;
}