static CURLcode tftp_translate_code(tftp_error_t error)
{
  CURLcode code = CURLE_OK;

  if(error != TFTP_ERR_NONE) {
    switch(error) {
    case TFTP_ERR_NOTFOUND:
      code = CURLE_TFTP_NOTFOUND;
      break;
    case TFTP_ERR_PERM:
      code = CURLE_TFTP_PERM;
      break;
    case TFTP_ERR_DISKFULL:
      code = CURLE_REMOTE_DISK_FULL;
      break;
    case TFTP_ERR_UNDEF:
    case TFTP_ERR_ILLEGAL:
      code = CURLE_TFTP_ILLEGAL;
      break;
    case TFTP_ERR_UNKNOWNID:
      code = CURLE_TFTP_UNKNOWNID;
      break;
    case TFTP_ERR_EXISTS:
      code = CURLE_REMOTE_FILE_EXISTS;
      break;
    case TFTP_ERR_NOSUCHUSER:
      code = CURLE_TFTP_NOSUCHUSER;
      break;
    case TFTP_ERR_TIMEOUT:
      code = CURLE_OPERATION_TIMEDOUT;
      break;
    case TFTP_ERR_NORESPONSE:
      code = CURLE_COULDNT_CONNECT;
      break;
    default:
      code= CURLE_ABORTED_BY_CALLBACK;
      break;
    }
  }
  else {
    code = CURLE_OK;
  }

  return(code);
}