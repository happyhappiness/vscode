{
    smtp->rcpt = smtp->rcpt->next;

    if(smtp->rcpt)
      /* Send the next RCPT TO command */
      result = smtp_perform_rcpt_to(conn);
    else {
      /* Send the DATA command */
      result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s", "DATA");

      if(!result)
        state(conn, SMTP_DATA);
    }
  }