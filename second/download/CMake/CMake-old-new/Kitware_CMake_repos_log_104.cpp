snprintf((char *)temp, sizeof(temp),
               "%c%c%c%c%s%c%c", CURL_IAC, CURL_SB, CURL_TELOPT_XDISPLOC,
               CURL_TELQUAL_IS, tn->subopt_xdisploc, CURL_IAC, CURL_SE);