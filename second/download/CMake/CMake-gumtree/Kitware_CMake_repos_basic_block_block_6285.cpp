{
    s_pSecFn->DeleteSecurityContext(digest->http_context);
    Curl_safefree(digest->http_context);
  }