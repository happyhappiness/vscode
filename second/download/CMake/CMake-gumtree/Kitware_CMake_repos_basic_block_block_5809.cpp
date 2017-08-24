f(data->multi_easy)
    /* when curl_easy_perform() is used, it creates its own multi handle to
       use and this is the one */
    curl_multi_cleanup(data->multi_easy)