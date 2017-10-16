        info[i].option = CURLFORM_FILECONTENT;
        info[i].value = contp+1;
        i++;
        info[i].option = CURLFORM_END;

        if(curl_formadd(httppost, last_post,
                        CURLFORM_ARRAY, info, CURLFORM_END ) != 0) {
          warnf(config->global, "curl_formadd failed, possibly the file %s is "
                "bad!\n", contp + 1);
          Curl_safefree(contents);
          return 6;
        }
      }
