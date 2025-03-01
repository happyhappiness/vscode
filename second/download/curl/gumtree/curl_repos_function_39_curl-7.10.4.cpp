CURLcode test(char *URL)
{
  CURL *curl;
  CURLcode res;
  FILE *hd_src ;
  int hd ;
  struct stat file_info;

  struct curl_slist *headerlist=NULL;
  const char *buf_1 = "RNFR 505";
  const char *buf_2 = "RNTO 505-forreal";

  /* get the file size of the local file */
  hd = open(arg2, O_RDONLY) ;
  if(hd == -1) {
    /* can't open file, bail out */
    return -1;
  }
  fstat(hd, &file_info);
  close(hd);

  /* get a FILE * of the same file, could also be made with
     fdopen() from the previous descriptor, but hey this is just 
     an example! */
  hd_src = fopen(arg2, "rb");
  if(NULL == hd_src) {
    return -2; /* if this happens things are major weird */
  }

  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* build a list of commands to pass to libcurl */
    headerlist = curl_slist_append(headerlist, buf_1);
    headerlist = curl_slist_append(headerlist, buf_2);

    /* enable uploading */
    curl_easy_setopt(curl, CURLOPT_UPLOAD, TRUE) ;

    /* enable verbose */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, TRUE) ;

    /* specify target */
    curl_easy_setopt(curl,CURLOPT_URL, URL);

    /* pass in that last of FTP commands to run after the transfer */
    curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);

    /* now specify which file to upload */
    curl_easy_setopt(curl, CURLOPT_INFILE, hd_src);

    /* and give the size of the upload (optional) */
    curl_easy_setopt(curl, CURLOPT_INFILESIZE, file_info.st_size);

    /* Now run off and do what you've been told! */
    res = curl_easy_perform(curl);

    /* clean up the FTP commands list */
    curl_slist_free_all (headerlist);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  fclose(hd_src); /* close the local file */

  curl_global_cleanup();
  return res;
}