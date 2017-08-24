result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s %s",
                           smtp->custom && smtp->custom[0] != '\0' ?
                           smtp->custom : "VRFY",
                           smtp->rcpt->data)