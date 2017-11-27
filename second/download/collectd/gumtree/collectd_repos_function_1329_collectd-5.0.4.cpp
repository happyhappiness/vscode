static void wh_callback_free (void *data) /* {{{ */
{
        wh_callback_t *cb;

        if (data == NULL)
                return;

        cb = data;

        wh_flush_nolock (/* timeout = */ 0, cb);

        curl_easy_cleanup (cb->curl);
        sfree (cb->location);
        sfree (cb->user);
        sfree (cb->pass);
        sfree (cb->credentials);
        sfree (cb->cacert);

        sfree (cb);
}