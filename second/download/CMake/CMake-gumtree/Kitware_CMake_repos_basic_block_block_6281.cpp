{ /* delete the context so a new one can be made */
      infof(data, "digest_sspi: MakeSignature failed, error 0x%08lx\n",
            (long)status);
      s_pSecFn->DeleteSecurityContext(digest->http_context);
      Curl_safefree(digest->http_context);
    }