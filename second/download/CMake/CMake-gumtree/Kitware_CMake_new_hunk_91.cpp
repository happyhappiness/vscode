  case CURLWC_DOWNLOADING: {
    /* filelist has at least one file, lets get first one */
    struct ftp_conn *ftpc = &conn->proto.ftpc;
    struct curl_fileinfo *finfo = wildcard->filelist.head->ptr;

    char *tmp_path = aprintf("%s%s", wildcard->path, finfo->filename);
    if(!tmp_path)
