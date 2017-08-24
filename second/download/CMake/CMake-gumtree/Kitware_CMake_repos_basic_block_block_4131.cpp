{
        free(http);
        (void)Curl_close(second);
        second = NULL;
      }