result = Curl_pp_sendf(&conn->proto.smtpc.pp, "RCPT TO:%s",
                           smtp->rcpt->data)