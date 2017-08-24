{
      conn->data->req.size =
        smb_swap64(((struct smb_nt_create_response *)msg)->end_of_file);
      Curl_pgrsSetDownloadSize(conn->data, conn->data->req.size);
      next_state = SMB_DOWNLOAD;
    }