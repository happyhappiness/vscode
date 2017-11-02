static CURLcode ftp_state_list(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  /* If this output is to be machine-parsed, the NLST command might be better
     to use, since the LIST command output is not specified or standard in any
     way. It has turned out that the NLST list output is not the same on all
     servers either... */

  /*
     if FTPFILE_NOCWD was specified, we are currently in
     the user's home directory, so we should add the path
     as argument for the LIST / NLST / or custom command.
     Whether the server will support this, is uncertain.

     The other ftp_filemethods will CWD into dir/dir/ first and
     then just do LIST (in that case: nothing to do here)
  */
  char *cmd,*lstArg,*slashPos;

  lstArg = NULL;
  if((data->set.ftp_filemethod == FTPFILE_NOCWD) &&
     data->state.path &&
     data->state.path[0] &&
     strchr(data->state.path,'/')) {

    lstArg = strdup(data->state.path);
    if(!lstArg)
      return CURLE_OUT_OF_MEMORY;

    /* Check if path does not end with /, as then we cut off the file part */
    if(lstArg[strlen(lstArg) - 1] != '/')  {

      /* chop off the file part if format is dir/dir/file */
      slashPos = strrchr(lstArg,'/');
      if(slashPos)
        *(slashPos+1) = '\0';
    }
  }

  cmd = aprintf( "%s%s%s",
                 data->set.str[STRING_CUSTOMREQUEST]?
                 data->set.str[STRING_CUSTOMREQUEST]:
                 (data->set.ftp_list_only?"NLST":"LIST"),
                 lstArg? " ": "",
                 lstArg? lstArg: "" );

  if(!cmd) {
    if(lstArg)
      free(lstArg);
    return CURLE_OUT_OF_MEMORY;
  }

  result = Curl_pp_sendf(&conn->proto.ftpc.pp, "%s", cmd);

  if(lstArg)
    free(lstArg);

  free(cmd);

  if(result)
    return result;

  state(conn, FTP_LIST);

  return result;
}