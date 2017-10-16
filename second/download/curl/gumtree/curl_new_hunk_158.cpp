        info[i].value = contp+1;
        i++;
        info[i].option = CURLFORM_END;

        if (curl_formadd(httppost, last_post,
                         CURLFORM_ARRAY, info, CURLFORM_END ) != 0) {
          warnf(config, "curl_formadd failed, possibly the file %s is bad!\n",
                contp+1);
          free(contents);
          return 6;
        }
      }
      else {
        info[i].option = CURLFORM_COPYCONTENTS;
        info[i].value = contp;
        i++;
        info[i].option = CURLFORM_END;
        if (curl_formadd(httppost, last_post,
                         CURLFORM_ARRAY, info, CURLFORM_END) != 0) {
          warnf(config, "curl_formadd failed!\n");
          free(contents);
          return 7;
        }
      }
    }

  }
  else {
    warnf(config, "Illegally formatted input field!\n");
    return 1;
  }
  free(contents);
  return 0;
}

