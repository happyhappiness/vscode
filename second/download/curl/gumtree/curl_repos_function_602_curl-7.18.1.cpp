const char *
curl_easy_strerror(CURLcode error)
{
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  switch (error) {
  case CURLE_OK:
    return "No error";

  case CURLE_UNSUPPORTED_PROTOCOL:
    return "Unsupported protocol";

  case CURLE_FAILED_INIT:
    return "Failed initialization";

  case CURLE_URL_MALFORMAT:
    return "URL using bad/illegal format or missing URL";

  case CURLE_COULDNT_RESOLVE_PROXY:
    return "Couldn't resolve proxy name";

  case CURLE_COULDNT_RESOLVE_HOST:
    return "Couldn't resolve host name";

  case CURLE_COULDNT_CONNECT:
    return "Couldn't connect to server";

  case CURLE_FTP_WEIRD_SERVER_REPLY:
    return "FTP: weird server reply";

  case CURLE_REMOTE_ACCESS_DENIED:
    return "Access denied to remote resource";

  case CURLE_FTP_WEIRD_PASS_REPLY:
    return "FTP: unknown PASS reply";

  case CURLE_FTP_WEIRD_PASV_REPLY:
    return "FTP: unknown PASV reply";

  case CURLE_FTP_WEIRD_227_FORMAT:
    return "FTP: unknown 227 response format";

  case CURLE_FTP_CANT_GET_HOST:
    return "FTP: can't figure out the host in the PASV response";

  case CURLE_FTP_COULDNT_SET_TYPE:
    return "FTP: couldn't set file type";

  case CURLE_PARTIAL_FILE:
    return "Transferred a partial file";

  case CURLE_FTP_COULDNT_RETR_FILE:
    return "FTP: couldn't retrieve (RETR failed) the specified file";

  case CURLE_QUOTE_ERROR:
    return "Quote command returned error";

  case CURLE_HTTP_RETURNED_ERROR:
    return "HTTP response code said error";

  case CURLE_WRITE_ERROR:
    return "Failed writing received data to disk/application";

  case CURLE_UPLOAD_FAILED:
    return "Upload failed (at start/before it took off)";

  case CURLE_READ_ERROR:
    return "Failed to open/read local data from file/application";

  case CURLE_OUT_OF_MEMORY:
    return "Out of memory";

  case CURLE_OPERATION_TIMEDOUT:
    return "Timeout was reached";

  case CURLE_FTP_PORT_FAILED:
    return "FTP: command PORT failed";

  case CURLE_FTP_COULDNT_USE_REST:
    return "FTP: command REST failed";

  case CURLE_RANGE_ERROR:
    return "Requested range was not delivered by the server";

  case CURLE_HTTP_POST_ERROR:
    return "Internal problem setting up the POST";

  case CURLE_SSL_CONNECT_ERROR:
    return "SSL connect error";

  case CURLE_BAD_DOWNLOAD_RESUME:
    return "Couldn't resume download";

  case CURLE_FILE_COULDNT_READ_FILE:
    return "Couldn't read a file:// file";

  case CURLE_LDAP_CANNOT_BIND:
    return "LDAP: cannot bind";

  case CURLE_LDAP_SEARCH_FAILED:
    return "LDAP: search failed";

  case CURLE_FUNCTION_NOT_FOUND:
    return "A required function in the library was not found";

  case CURLE_ABORTED_BY_CALLBACK:
    return "Operation was aborted by an application callback";

  case CURLE_BAD_FUNCTION_ARGUMENT:
    return "A libcurl function was given a bad argument";

  case CURLE_INTERFACE_FAILED:
    return "Failed binding local connection end";

  case CURLE_TOO_MANY_REDIRECTS :
    return "Number of redirects hit maximum amount";

  case CURLE_UNKNOWN_TELNET_OPTION:
    return "User specified an unknown telnet option";

  case CURLE_TELNET_OPTION_SYNTAX :
    return "Malformed telnet option";

  case CURLE_PEER_FAILED_VERIFICATION:
    return "SSL peer certificate or SSH md5 fingerprint was not OK";

  case CURLE_GOT_NOTHING:
    return "Server returned nothing (no headers, no data)";

  case CURLE_SSL_ENGINE_NOTFOUND:
    return "SSL crypto engine not found";

  case CURLE_SSL_ENGINE_SETFAILED:
    return "Can not set SSL crypto engine as default";

  case CURLE_SSL_ENGINE_INITFAILED:
    return "Failed to initialise SSL crypto engine";

  case CURLE_SEND_ERROR:
    return "Failed sending data to the peer";

  case CURLE_RECV_ERROR:
    return "Failure when receiving data from the peer";

  case CURLE_SSL_CERTPROBLEM:
    return "Problem with the local SSL certificate";

  case CURLE_SSL_CIPHER:
    return "Couldn't use specified SSL cipher";

  case CURLE_SSL_CACERT:
    return "Peer certificate cannot be authenticated with known CA certificates";

  case CURLE_SSL_CACERT_BADFILE:
    return "Problem with the SSL CA cert (path? access rights?)";

  case CURLE_BAD_CONTENT_ENCODING:
    return "Unrecognized HTTP Content-Encoding";

  case CURLE_LDAP_INVALID_URL:
    return "Invalid LDAP URL";

  case CURLE_FILESIZE_EXCEEDED:
    return "Maximum file size exceeded";

  case CURLE_USE_SSL_FAILED:
    return "Requested SSL level failed";

  case CURLE_SSL_SHUTDOWN_FAILED:
    return "Failed to shut down the SSL connection";

  case CURLE_SEND_FAIL_REWIND:
    return "Send failed since rewinding of the data stream failed";

  case CURLE_LOGIN_DENIED:
    return "Login denied";

  case CURLE_TFTP_NOTFOUND:
    return "TFTP: File Not Found";

  case CURLE_TFTP_PERM:
    return "TFTP: Access Violation";

  case CURLE_REMOTE_DISK_FULL:
    return "Disk full or allocation exceeded";

  case CURLE_TFTP_ILLEGAL:
    return "TFTP: Illegal operation";

  case CURLE_TFTP_UNKNOWNID:
    return "TFTP: Unknown transfer ID";

  case CURLE_REMOTE_FILE_EXISTS:
    return "Remote file already exists";

  case CURLE_TFTP_NOSUCHUSER:
    return "TFTP: No such user";

  case CURLE_CONV_FAILED:
    return "Conversion failed";

  case CURLE_CONV_REQD:
    return "Caller must register CURLOPT_CONV_ callback options";

  case CURLE_REMOTE_FILE_NOT_FOUND:
    return "Remote file not found";

  case CURLE_SSH:
    return "Error in the SSH layer";

    /* error codes not used by current libcurl */
  case CURLE_OBSOLETE4:
  case CURLE_OBSOLETE10:
  case CURLE_OBSOLETE12:
  case CURLE_OBSOLETE16:
  case CURLE_OBSOLETE20:
  case CURLE_OBSOLETE24:
  case CURLE_OBSOLETE29:
  case CURLE_OBSOLETE32:
  case CURLE_OBSOLETE40:
  case CURLE_OBSOLETE44:
  case CURLE_OBSOLETE46:
  case CURLE_OBSOLETE50:
  case CURLE_OBSOLETE57:
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
  return "Unknown error";
#else
  if(error == CURLE_OK)
    return "No error";
  else
    return "Error";
#endif
}