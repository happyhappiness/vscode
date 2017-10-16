        }
        forms[count].option = CURLFORM_END;
        FreeMultiInfo (multi_start);
        if (curl_formadd(httppost, last_post,
                         CURLFORM_COPYNAME, name,
                         CURLFORM_ARRAY, forms, CURLFORM_END) != 0) {
          fprintf(stderr, "curl_formadd failed!\n");
          free(forms);
          free(contents);
          return 5;
        }
        free(forms);
      }
