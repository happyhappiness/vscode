{
    /* read NSPR error code */
    err = PR_GetError();
    if(is_cc_error(err))
      curlerr = CURLE_SSL_CERTPROBLEM;

    /* print the error number and error string */
    infof(data, "NSS error %d (%s)\n", err, nss_error_to_name(err));

    /* print a human-readable message describing the error if available */
    nss_print_error_message(data, err);
  }