     http://www.fngtps.com/2006/09/http-authentication

  */



  if(authp->iestyle && ((tmp = strchr((char *)uripath, '?')) != NULL)) {

    size_t urilen = tmp - (char *)uripath;



    path = (unsigned char *) aprintf("%.*s", urilen, uripath);

  }

  else

    path = (unsigned char *) strdup((char *) uripath);



  if(!path)

    return CURLE_OUT_OF_MEMORY;



  result = Curl_sasl_create_digest_http_message(data, userp, passwdp, request,

                                                path, digest, &response, &len);

  free(path);

  if(result)

    return result;



  *allocuserpwd = aprintf("%sAuthorization: Digest %s\r\n",

                          proxy ? "Proxy-" : "",

                          response);

  free(response);

  if(!*allocuserpwd)

    return CURLE_OUT_OF_MEMORY;



  authp->done = TRUE;



  return CURLE_OK;

}



void Curl_digest_cleanup(struct SessionHandle *data)

{

  Curl_sasl_digest_cleanup(&data->state.digest);

  Curl_sasl_digest_cleanup(&data->state.proxydigest);

}



#endif
