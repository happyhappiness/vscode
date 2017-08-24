{
      binddn = conn->user;
      passwd.bv_val = conn->passwd;
      passwd.bv_len = strlen(passwd.bv_val);
    }