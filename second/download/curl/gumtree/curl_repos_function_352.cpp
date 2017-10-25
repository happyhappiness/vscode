const char *
curl_easy_strerror(CURLcode error)
{
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  switch (error) {
  case CURLE_OK:
    return "no error";

  case CURLE_UNSUPPORTED_PROTOCOL:
    return "unsupported protocol";

  case CURLE_FAILED_INIT:
    return "failed init";

  case CURLE_URL_MALFORMAT:
    return "URL using bad/illegal format or missing URL";

  case CURLE_COULDNT_RESOLVE_PROXY:
    return "couldnt resolve proxy name";

  case CURLE_COULDNT_RESOLVE_HOST:
    return "couldnt resolve host name";

  case CURLE_COULDNT_CONNECT:
    return "couldn't connect to server";

  case CURLE_FTP_WEIRD_SERVER_REPLY:
    return "FTP: weird server reply";

  case CURLE_FTP_ACCESS_DENIED:
    return "FTP: access denied";

  case CURLE_FTP_USER_PASSWORD_INCORRECT:
    return "FTP: user and/or password incorrect";

  case CURLE_FTP_WEIRD_PASS_REPLY:
    return "FTP: unknown PASS reply";

  case CURLE_FTP_WEIRD_USER_REPLY:
    return "FTP: unknown USER reply";

  case CURLE_FTP_WEIRD_PASV_REPLY:
    return "FTP: unknown PASV reply";

  case CURLE_FTP_WEIRD_227_FORMAT:
    return "FTP: unknown 227 response format";

  case CURLE_FTP_CANT_GET_HOST:
    return "FTP: can't figure out the host in the PASV response";

  case CURLE_FTP_CANT_RECONNECT:
    return "FTP: can't connect to server the response code is unknown";

  case CURLE_FTP_COULDNT_SET_BINARY:
    return "FTP: couldn't set binary mode";

  case CURLE_PARTIAL_FILE:
    return "Transferred a partial file";

  case CURLE_FTP_COULDNT_RETR_FILE:
    return "FTP: couldn't retrieve (RETR failed) the specified file";

  case CURLE_FTP_WRITE_ERROR:
    return "FTP: the post-transfer acknowledge response was not OK";

  case CURLE_FTP_QUOTE_ERROR:
    return "FTP: a quote command returned error";

  case CURLE_HTTP_RETURNED_ERROR:
    return "HTTP response code said error";

  case CURLE_WRITE_ERROR:
    return "failed writing received data to disk/application";

  case CURLE_FTP_COULDNT_STOR_FILE:
    return "failed FTP upload (the STOR command)";

  case CURLE_READ_ERROR:
    return "failed to open/read local data from file/application";

  case CURLE_OUT_OF_MEMORY:
    return "out of memory";

  case CURLE_OPERATION_TIMEOUTED:
    return "a timeout was reached";

  case CURLE_FTP_COULDNT_SET_ASCII:
    return "FTP could not set ASCII mode (TYPE A)";

  case CURLE_FTP_PORT_FAILED:
    return "FTP command PORT failed";

  case CURLE_FTP_COULDNT_USE_REST:
    return "FTP command REST failed";

  case CURLE_FTP_COULDNT_GET_SIZE:
    return "FTP command SIZE failed";

  case CURLE_HTTP_RANGE_ERROR:
    return "a range was requested but the server did not deliver it";

  case CURLE_HTTP_POST_ERROR:
    return "internal problem setting up the POST";

  case CURLE_SSL_CONNECT_ERROR:
    return "SSL connect error";

  case CURLE_BAD_DOWNLOAD_RESUME:
    return "couldn't resume download";

  case CURLE_FILE_COULDNT_READ_FILE:
    return "couldn't read a file:// file";

  case CURLE_LDAP_CANNOT_BIND:
    return "LDAP: cannot bind";

  case CURLE_LDAP_SEARCH_FAILED:
    return "LDAP: search failed";

  case CURLE_LIBRARY_NOT_FOUND:
    return "a required shared library was not found";

  case CURLE_FUNCTION_NOT_FOUND:
    return "a required function in the shared library was not found";

  case CURLE_ABORTED_BY_CALLBACK:
    return "the operation was aborted by an application callback";

  case CURLE_BAD_FUNCTION_ARGUMENT:
    return "a libcurl function was given a bad argument";

  case CURLE_INTERFACE_FAILED:
    return "failed binding local connection end";

  case CURLE_TOO_MANY_REDIRECTS :
    return "number of redirects hit maximum amount";

  case CURLE_UNKNOWN_TELNET_OPTION:
    return "User specified an unknown option";

  case CURLE_TELNET_OPTION_SYNTAX :
    return "Malformed telnet option";

  case CURLE_SSL_PEER_CERTIFICATE:
    return "SSL peer certificate was not ok";

  case CURLE_GOT_NOTHING:
    return "server returned nothing (no headers, no data)";

  case CURLE_SSL_ENGINE_NOTFOUND:
    return "SSL crypto engine not found";

  case CURLE_SSL_ENGINE_SETFAILED:
    return "can not set SSL crypto engine as default";

  case CURLE_SSL_ENGINE_INITFAILED:
    return "failed to initialise SSL crypto engine";

  case CURLE_SEND_ERROR:
    return "failed sending data to the peer";

  case CURLE_RECV_ERROR:
    return "failure when receiving data from the peer";

  case CURLE_SHARE_IN_USE:
    return "share is already in use";

  case CURLE_SSL_CERTPROBLEM:
    return "problem with the local SSL certificate";

  case CURLE_SSL_CIPHER:
    return "couldn't use specified SSL cipher";

  case CURLE_SSL_CACERT:
    return "problem with the SSL CA cert (path? access rights?)";

  case CURLE_BAD_CONTENT_ENCODING:
    return "Unrecognized HTTP Content-Encoding";

  case CURLE_LDAP_INVALID_URL:
    return "Invalid LDAP URL";

  case CURLE_FILESIZE_EXCEEDED:
    return "Maximum file size exceeded";

  case CURLE_FTP_SSL_FAILED:
    return "Requested FTP SSL level failed";

  case CURLE_SEND_FAIL_REWIND:
    return "Send failed since rewinding of the data stream failed";

  case CURLE_LOGIN_DENIED:
    return "FTP: login denied";;

  case CURLE_URL_MALFORMAT_USER: /* not used by current libcurl */
  case CURLE_MALFORMAT_USER:     /* not used by current libcurl */
  case CURLE_BAD_CALLING_ORDER:  /* not used by current libcurl */
  case CURLE_BAD_PASSWORD_ENTERED:/* not used by current libcurl */
  case CURLE_OBSOLETE:           /* not used by current libcurl */
  case CURL_LAST:
    break;
  }
  /*
   * By using a switch, gcc -Wall will complain about enum values
   * which do not appear, helping keep this function up-to-date.
   * By using gcc -Wall -Werror, you can't forget.
   *
   * A table would not have the same benefit.  Most compilers will
   * generate code very similar to a table in any case, so there
   * is little performance gain from a table.  And something is broken
   * for the user's application, anyways, so does it matter how fast
   * it _doesn't_ work?
   *
   * The line number for the error will be near this comment, which
   * is why it is here, and not at the start of the switch.
   */
  return "unknown error";
#else
  if (error == CURLE_OK)
    return "no error";
  else
    return "error";
#endif
}