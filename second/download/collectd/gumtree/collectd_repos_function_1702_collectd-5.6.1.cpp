static int wh_post_nolock (wh_callback_t *cb, char const *data) /* {{{ */
{
        int status = 0;

        curl_easy_setopt (cb->curl, CURLOPT_POSTFIELDS, data);
        status = curl_easy_perform (cb->curl);

        wh_log_http_error (cb);

        if (status != CURLE_OK)
        {
                ERROR ("write_http plugin: curl_easy_perform failed with "
                                "status %i: %s",
                                status, cb->curl_errbuf);
        }
        return (status);
}