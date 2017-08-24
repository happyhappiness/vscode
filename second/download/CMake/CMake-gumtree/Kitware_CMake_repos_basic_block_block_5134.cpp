{
        /* We found the end of the response lines, but we didn't parse the
           full chunk of data we have read from the server. We therefore need
           to store the rest of the data to be checked on the next invoke as
           it may actually contain another end of response already! */
        clipamount = gotbytes - i;
        restart = TRUE;
        DEBUGF(infof(data, "Curl_pp_readresp_ %d bytes of trailing "
                     "server response left\n",
                     (int)clipamount));
      }