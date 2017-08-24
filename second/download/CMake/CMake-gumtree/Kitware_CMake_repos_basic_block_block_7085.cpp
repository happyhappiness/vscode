f(!result) {
      if(((ccert_context->dwCertEncodingType & X509_ASN_ENCODING) != 0) &&
         (ccert_context->cbCertEncoded > 0)) {

        const char *beg = (const char *) ccert_context->pbCertEncoded;
        const char *end = beg + ccert_context->cbCertEncoded;
        result = Curl_extract_certinfo(conn, 0, beg, end);
      }
    }