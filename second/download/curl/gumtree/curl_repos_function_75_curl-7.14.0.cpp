int main(int argc, char **argv) {

  BIO* in=NULL;
  BIO* out=NULL;

  char * outfile = NULL;
  char * infile = NULL ;

  int tabLength=100;
  char *binaryptr;
  char* mimetype;
  char* mimetypeaccept=NULL;
  char* contenttype;
  char** pp;
  unsigned char* hostporturl = NULL;
  binaryptr=(char*)malloc(tabLength);
  BIO * p12bio ;
  char **args = argv + 1;
  unsigned char * serverurl;
  sslctxparm p;
  char *response;
  p.verbose = 0;

  CURLcode res;
  struct curl_slist * headers=NULL;

  p.errorbio = BIO_new_fp (stderr, BIO_NOCLOSE);

  curl_global_init(CURL_GLOBAL_DEFAULT);

  /* we need some more for the P12 decoding */

  OpenSSL_add_all_ciphers();
  OpenSSL_add_all_digests();
  ERR_load_crypto_strings();


  int badarg=0;

  while (*args && *args[0] == '-') {
    if (!strcmp (*args, "-in")) {
      if (args[1]) {
        infile=*(++args);
      } else badarg=1;
    } else if (!strcmp (*args, "-out")) {
      if (args[1]) {
        outfile=*(++args);
      } else badarg=1;
    } else if (!strcmp (*args, "-p12")) {
      if (args[1]) {
        p.p12file = *(++args);
      } else badarg=1;
    } else if (strcmp(*args,"-envpass") == 0) {
      if (args[1]) {
        p.pst = getenv(*(++args));
      } else badarg=1;
    } else if (strcmp(*args,"-connect") == 0) {
      if (args[1]) {
        hostporturl = *(++args);
      } else badarg=1;
    } else if (strcmp(*args,"-mimetype") == 0) {
      if (args[1]) {
        mimetype = *(++args);
      } else badarg=1;
    } else if (strcmp(*args,"-acceptmime") == 0) {
      if (args[1]) {
        mimetypeaccept = *(++args);
      } else badarg=1;
    } else if (strcmp(*args,"-accesstype") == 0) {
      if (args[1]) {
        if ((p.accesstype = OBJ_obj2nid(OBJ_txt2obj(*++args,0))) == 0) badarg=1;
      } else badarg=1;
    } else if (strcmp(*args,"-verbose") == 0) {
      p.verbose++;
    } else badarg=1;
    args++;
  }

  if (mimetype==NULL || mimetypeaccept == NULL) badarg = 1;

  if (badarg) {
    for (pp=curlx_usage; (*pp != NULL); pp++)
      BIO_printf(p.errorbio,"%s\n",*pp);
    BIO_printf(p.errorbio,"\n");
    goto err;
  }



  /* set input */

  if ((in=BIO_new(BIO_s_file())) == NULL) {
    BIO_printf(p.errorbio, "Error setting input bio\n");
    goto err;
  } else if (infile == NULL)
    BIO_set_fp(in,stdin,BIO_NOCLOSE|BIO_FP_TEXT);
  else if (BIO_read_filename(in,infile) <= 0) {
    BIO_printf(p.errorbio, "Error opening input file %s\n", infile);
    BIO_free(in);
    goto err;
  }

  /* set output  */

  if ((out=BIO_new(BIO_s_file())) == NULL) {
    BIO_printf(p.errorbio, "Error setting output bio.\n");
    goto err;
  } else if (outfile == NULL)
    BIO_set_fp(out,stdout,BIO_NOCLOSE|BIO_FP_TEXT);
  else if (BIO_write_filename(out,outfile) <= 0) {
    BIO_printf(p.errorbio, "Error opening output file %s\n", outfile);
    BIO_free(out);
    goto err;
  }


  p.errorbio = BIO_new_fp (stderr, BIO_NOCLOSE);

  if (!(p.curl = curl_easy_init())) {
    BIO_printf(p.errorbio, "Cannot init curl lib\n");
    goto err;
  }



  if (!(p12bio = BIO_new_file(p.p12file , "rb"))) {
    BIO_printf(p.errorbio, "Error opening P12 file %s\n", p.p12file); goto err;
  }
  if (!(p.p12 = d2i_PKCS12_bio (p12bio, NULL))) {
    BIO_printf(p.errorbio, "Cannot decode P12 structure %s\n", p.p12file); goto err;
  }

  p.ca= NULL;
  if (!(PKCS12_parse (p.p12, p.pst, &(p.pkey), &(p.usercert), &(p.ca) ) )) {
    BIO_printf(p.errorbio,"Invalid P12 structure in %s\n", p.p12file); goto err;
  }

  if (sk_X509_num(p.ca) <= 0) {
    BIO_printf(p.errorbio,"No trustworthy CA given.%s\n", p.p12file); goto err;
  }

  if (p.verbose > 1)
    X509_print_ex(p.errorbio,p.usercert,0,0);

  /* determine URL to go */

  if (hostporturl) {
    serverurl=(char*) malloc(9+strlen(hostporturl));
    sprintf(serverurl,"https://%s",hostporturl);
  }
  else if (p.accesstype != 0) { /* see whether we can find an AIA or SIA for a given access type */
    if (!(serverurl = my_get_ext(p.usercert,p.accesstype,NID_info_access))) {
      BIO_printf(p.errorbio,"no service URL in user cert "
                 "cherching in others certificats\n");
      int j=0;
      int find=0;
      for (j=0;j<sk_X509_num(p.ca);j++) {
        if ((serverurl = my_get_ext(sk_X509_value(p.ca,j),p.accesstype,
                                    NID_info_access)))
          break;
        if ((serverurl = my_get_ext(sk_X509_value(p.ca,j),p.accesstype,
                                    NID_sinfo_access)))
          break;
      }
    }
  }

  if (!serverurl) {
    BIO_printf(p.errorbio, "no service URL in certificats,"
               " check '-accesstype (AD_DVCS | ad_timestamping)'"
               " or use '-connect'\n");
    goto err;
  }

  if (p.verbose)
    BIO_printf(p.errorbio, "Service URL: <%s>\n", serverurl);

  curl_easy_setopt(p.curl, CURLOPT_URL, serverurl);

  /* Now specify the POST binary data */

  curl_easy_setopt(p.curl, CURLOPT_POSTFIELDS, binaryptr);
  curl_easy_setopt(p.curl, CURLOPT_POSTFIELDSIZE,tabLength);

  /* pass our list of custom made headers */

  contenttype=(char*) malloc(15+strlen(mimetype));
  sprintf(contenttype,"Content-type: %s",mimetype);
  headers = curl_slist_append(headers,contenttype);
  curl_easy_setopt(p.curl, CURLOPT_HTTPHEADER, headers);

  if (p.verbose)
    BIO_printf(p.errorbio, "Service URL: <%s>\n", serverurl);

  {
    FILE *outfp;
    BIO_get_fp(out,&outfp);
    curl_easy_setopt(p.curl, CURLOPT_FILE,outfp);
  }

  res = curl_easy_setopt(p.curl, CURLOPT_SSL_CTX_FUNCTION, sslctxfun)  ;

  if (res != CURLE_OK)
    BIO_printf(p.errorbio,"%d %s=%d %d\n", __LINE__, "CURLOPT_SSL_CTX_FUNCTION",CURLOPT_SSL_CTX_FUNCTION,res);

  curl_easy_setopt(p.curl, CURLOPT_SSL_CTX_DATA, &p);

  {
    int lu; int i=0;
    while ((lu = BIO_read (in,&binaryptr[i],tabLength-i)) >0 ) {
      i+=lu;
      if (i== tabLength) {
        tabLength+=100;
        binaryptr=(char*)realloc(binaryptr,tabLength); /* should be more careful */
      }
    }
    tabLength = i;
  }
  /* Now specify the POST binary data */

  curl_easy_setopt(p.curl, CURLOPT_POSTFIELDS, binaryptr);
  curl_easy_setopt(p.curl, CURLOPT_POSTFIELDSIZE,tabLength);


  /* Perform the request, res will get the return code */

  BIO_printf(p.errorbio,"%d %s %d\n", __LINE__, "curl_easy_perform",
             res = curl_easy_perform(p.curl));
  {
    int result =curl_easy_getinfo(p.curl,CURLINFO_CONTENT_TYPE,&response);
    if( mimetypeaccept && p.verbose)
      if(!strcmp(mimetypeaccept,response))
        BIO_printf(p.errorbio,"the response has a correct mimetype : %s\n",
                   response);
      else
        BIO_printf(p.errorbio,"the reponse doesn\'t has an acceptable "
                   "mime type, it is %s instead of %s\n",
                   response,mimetypeaccept);
  }

  /*** code d'erreur si accept mime ***, egalement code return HTTP != 200 ***/

/* free the header list*/

  curl_slist_free_all(headers);

  /* always cleanup */
  curl_easy_cleanup(p.curl);

  BIO_free(in);
  BIO_free(out);
  return (EXIT_SUCCESS);

  err: BIO_printf(p.errorbio,"error");
  exit(1);
}