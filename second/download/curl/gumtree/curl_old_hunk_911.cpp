        }
        forms[count].option = CURLFORM_END;
        FreeMultiInfo(&multi_start, &multi_current);
        if(curl_formadd(httppost, last_post,
                        CURLFORM_COPYNAME, name,
                        CURLFORM_ARRAY, forms, CURLFORM_END) != 0) {
          warnf(config, "curl_formadd failed!\n");
          Curl_safefree(forms);
          Curl_safefree(contents);
          return 5;
        }
        Curl_safefree(forms);
      }
