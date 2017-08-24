result = Curl_pp_sendf(&conn->proto.smtpc.pp,
                           "MAIL FROM:%s AUTH=%s SIZE=%s", from, auth, size)