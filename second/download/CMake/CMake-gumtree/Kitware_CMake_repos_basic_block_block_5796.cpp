f(passwdp) {
      Curl_safefree(*passwdp);
      *passwdp = passwd;
    }