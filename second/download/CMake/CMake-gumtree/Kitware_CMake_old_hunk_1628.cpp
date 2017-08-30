{

  struct FTP *ftp= conn->proto.ftp;



  /* The FTP session may or may not have been allocated/setup at this point! */

  if(ftp) {

    if(ftp->entrypath)

      free(ftp->entrypath);

    if(ftp->cache)

      free(ftp->cache);

    if(ftp->file)

      free(ftp->file);

    if(ftp->dir)

      free(ftp->dir);



    ftp->file = ftp->dir = NULL; /* zero */

  }

  return CURLE_OK;

}



/*

 * local variables:

 * eval: (load-file "../curl-mode.el")

 * end:

 * vim600: fdm=marker

 * vim: et sw=2 ts=2 sts=2 tw=78

 */



#endif /* CURL_DISABLE_FTP */
