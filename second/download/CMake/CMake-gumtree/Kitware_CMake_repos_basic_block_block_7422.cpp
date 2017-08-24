{
  case 1:
    /* an alternative name matched the server hostname */
    infof(data, "\t subjectAltName: %s matched\n", dispname);
    return CURLE_OK;
  case 0:
    /* an alternative name field existed, but didn't match and then
       we MUST fail */
    infof(data, "\t subjectAltName does not match %s\n", dispname);
    return CURLE_PEER_FAILED_VERIFICATION;
  }