snprintf((char *)temp, sizeof(temp),
               "%c%c%c%c%s%c%c", CURL_IAC, CURL_SB, CURL_TELOPT_TTYPE,
               CURL_TELQUAL_IS, tn->subopt_ttype, CURL_IAC, CURL_SE);