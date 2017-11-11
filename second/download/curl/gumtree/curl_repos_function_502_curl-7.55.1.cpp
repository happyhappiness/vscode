int test(char *URL)
{
  CURLcode res;
  CURL *curl;
  char *ipstr=NULL;

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  test_setopt(curl, CURLOPT_URL, URL);
  test_setopt(curl, CURLOPT_HEADER, 1L);

  libtest_debug_config.nohex = 1;
  libtest_debug_config.tracetime = 1;
  test_setopt(curl, CURLOPT_DEBUGDATA, &libtest_debug_config);
  test_setopt(curl, CURLOPT_DEBUGFUNCTION, libtest_debug_cb);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  if(libtest_arg3 && !strcmp(libtest_arg3, "activeftp"))
    test_setopt(curl, CURLOPT_FTPPORT, "-");

  setupcallbacks(curl);

  res = curl_easy_perform(curl);

  if(!res) {
    res = curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &ipstr);
    if(libtest_arg2) {
      FILE *moo = fopen(libtest_arg2, "wb");
      if(moo) {
        double time_namelookup;
        double time_connect;
        double time_pretransfer;
        double time_starttransfer;
        double time_total;
        fprintf(moo, "IP: %s\n", ipstr);
        curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &time_namelookup);
        curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &time_connect);
        curl_easy_getinfo(curl, CURLINFO_PRETRANSFER_TIME, &time_pretransfer);
        curl_easy_getinfo(curl, CURLINFO_STARTTRANSFER_TIME,
                          &time_starttransfer);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &time_total);

        /* since the timing will always vary we only compare relative
           differences between these 5 times */
        if(time_namelookup > time_connect) {
          fprintf(moo, "namelookup vs connect: %f %f\n",
                  time_namelookup, time_connect);
        }
        if(time_connect > time_pretransfer) {
          fprintf(moo, "connect vs pretransfer: %f %f\n",
                  time_connect, time_pretransfer);
        }
        if(time_pretransfer > time_starttransfer) {
          fprintf(moo, "pretransfer vs starttransfer: %f %f\n",
                  time_pretransfer, time_starttransfer);
        }
        if(time_starttransfer > time_total) {
          fprintf(moo, "starttransfer vs total: %f %f\n",
                  time_starttransfer, time_total);
        }

        fclose(moo);
      }
    }
  }

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}