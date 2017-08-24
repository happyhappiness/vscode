r(i = 0; i < nread; i++) {
      outbuf[j++] = buffer[i];
      if((unsigned char)buffer[i] == CURL_IAC)
        outbuf[j++] = CURL_IAC;
    }