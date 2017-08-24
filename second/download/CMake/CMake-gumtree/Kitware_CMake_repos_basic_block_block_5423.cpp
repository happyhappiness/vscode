{
      failf(data, "STARTTLS denied, code %d", smtpcode);
      result = CURLE_USE_SSL_FAILED;
    }