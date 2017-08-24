f(progress == SASL_INPROGRESS)
      state(conn, SMTP_AUTH);
    else {
      /* Other mechanisms not supported */
      infof(conn->data, "No known authentication mechanisms supported!\n");
      result = CURLE_LOGIN_DENIED;
    }