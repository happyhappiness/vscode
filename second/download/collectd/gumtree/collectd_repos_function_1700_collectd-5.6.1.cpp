static void wh_log_http_error (wh_callback_t *cb)
{
        if (!cb->log_http_error)
                return;

        long http_code = 0;

        curl_easy_getinfo (cb->curl, CURLINFO_RESPONSE_CODE, &http_code);

        if (http_code != 200)
                INFO ("write_http plugin: HTTP Error code: %lu", http_code);
}