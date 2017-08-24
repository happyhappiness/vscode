{
          dns->timestamp = 0; /* mark as added by CURLOPT_RESOLVE */
          /* release the returned reference; the cache itself will keep the
           * entry alive: */
          dns->inuse--;
        }