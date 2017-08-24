{
    p = Curl_getASN1Element(&elem, param->beg, param->end);
    do_pubkey_field(data, certnum, "dsa(p)", &elem);
    p = Curl_getASN1Element(&elem, p, param->end);
    do_pubkey_field(data, certnum, "dsa(q)", &elem);
    Curl_getASN1Element(&elem, p, param->end);
    do_pubkey_field(data, certnum, "dsa(g)", &elem);
    do_pubkey_field(data, certnum, "dsa(pub_key)", &pk);
  }