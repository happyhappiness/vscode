{
    failf(data, "DATA failed: %d", smtpcode);
    result = CURLE_SEND_ERROR;
  }