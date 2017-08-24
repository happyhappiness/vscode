{

          /* Setup identity's domain and length */
          domain.tchar_ptr = Curl_convert_UTF8_to_tchar((char *) content);
          if(!domain.tchar_ptr)
            return CURLE_OUT_OF_MEMORY;

          dup_domain.tchar_ptr = _tcsdup(domain.tchar_ptr);
          if(!dup_domain.tchar_ptr) {
            Curl_unicodefree(domain.tchar_ptr);
            return CURLE_OUT_OF_MEMORY;
          }

          free(identity->Domain);
          identity->Domain = dup_domain.tbyte_ptr;
          identity->DomainLength = curlx_uztoul(_tcslen(dup_domain.tchar_ptr));
          dup_domain.tchar_ptr = NULL;

          Curl_unicodefree(domain.tchar_ptr);
        }