{
              struct WildcardData *wc = &data->wildcard;
              if(wc->state == CURLWC_DONE || wc->state == CURLWC_SKIP) {
                /* skip some states if it is important */
                multi_done(&data->easy_conn, CURLE_OK, FALSE);
                multistate(data, CURLM_STATE_DONE);
                rc = CURLM_CALL_MULTI_PERFORM;
                break;
              }
            }