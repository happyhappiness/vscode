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
      else {
#ifdef CURL_DOES_CONVERSIONS
        if(convert_to_network(contp, strlen(contp))) {
          warnf(config->global, "curl_formadd failed!\n");
          Curl_safefree(contents);
          return 7;
        }
#endif
        info[i].option = CURLFORM_COPYCONTENTS;
        info[i].value = contp;
        i++;
        info[i].option = CURLFORM_END;
        if(curl_formadd(httppost, last_post,
                        CURLFORM_ARRAY, info, CURLFORM_END) != 0) {
          warnf(config->global, "curl_formadd failed!\n");
          Curl_safefree(contents);
          return 8;
        }
      }
    }

  }
  else {
    warnf(config->global, "Illegally formatted input field!\n");
    return 1;
  }
  Curl_safefree(contents);
  return 0;
}
