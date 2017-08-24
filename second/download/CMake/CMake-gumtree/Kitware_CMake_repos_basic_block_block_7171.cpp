{
    infof(data, "schannel: clear security context handle\n");
    s_pSecFn->DeleteSecurityContext(&connssl->ctxt->ctxt_handle);
    Curl_safefree(connssl->ctxt);
  }