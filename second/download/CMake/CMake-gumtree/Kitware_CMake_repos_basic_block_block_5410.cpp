result = Curl_pp_sendf(&conn->proto.smtpc.pp,
                           "MAIL FROM:%s", from)