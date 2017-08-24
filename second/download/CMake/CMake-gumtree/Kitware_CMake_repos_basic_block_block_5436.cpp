{
      failf(data, "Remote access denied: %d", smtpcode);
      result = CURLE_REMOTE_ACCESS_DENIED;
    }