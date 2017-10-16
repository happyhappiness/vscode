          ;
        }
        else if(result && global->showerror) {
          fprintf(global->errors, "curl: (%d) %s\n", result, (errorbuffer[0]) ?
                  errorbuffer : curl_easy_strerror(result));
          if(result == CURLE_SSL_CACERT)
            fputs(CURL_CA_CERT_ERRORMSG, global->errors);
        }

        /* Fall through comment to 'quit_urls' label */

        /*
        ** Upon error condition and always that a message has already been
