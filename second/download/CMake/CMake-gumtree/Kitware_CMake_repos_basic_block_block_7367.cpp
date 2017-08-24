{
    p = Curl_getASN1Element(&elem, param->beg, param->end);
    do_pubkey_field(data, certnum, "dh(p)", &elem);
    Curl_getASN1Element(&elem, param->beg, param->end);
    do_pubkey_field(data, certnum, "dh(g)", &elem);
    do_pubkey_field(data, certnum, "dh(pub_key)", &pk);
  }