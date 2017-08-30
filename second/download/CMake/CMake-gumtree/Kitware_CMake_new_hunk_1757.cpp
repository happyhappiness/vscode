       */



      if((res == CURLE_OK) && newurl) {

        res = Curl_follow(data, newurl);

        if(CURLE_OK == res) {

          newurl = NULL;

          continue;

        }

      }

    }

    break; /* it only reaches here when this shouldn't loop */

