          ns = testing_ptr;

        }

      }



#ifdef CURL_DOES_CONVERSIONS

/* escape sequences are always in ASCII so convert them on non-ASCII hosts */

      if (!handle ||

          (Curl_convert_to_network(handle, &in, 1) != CURLE_OK)) {

        /* Curl_convert_to_network calls failf if unsuccessful */

        free(ns);

        return NULL;

      }

#endif /* CURL_DOES_CONVERSIONS */



      snprintf(&ns[strindex], 4, "%%%02X", in);



      strindex+=3;

