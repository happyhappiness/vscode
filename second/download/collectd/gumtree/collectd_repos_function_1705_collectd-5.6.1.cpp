static void wh_callback_free (void *data) /* {{{ */
{
        wh_callback_t *cb;

        if (data == NULL)
                return;

        cb = data;

        if (cb->send_buffer != NULL)
                wh_flush_nolock (/* timeout = */ 0, cb);

        if (cb->curl != NULL)
        {
                curl_easy_cleanup (cb->curl);
                cb->curl = NULL;
        }

        if (cb->headers != NULL)
        {
                curl_slist_free_all (cb->headers);
                cb->headers = NULL;
        }

        sfree (cb->name);
        sfree (cb->location);
        sfree (cb->user);
        sfree (cb->pass);
        sfree (cb->credentials);
        sfree (cb->cacert);
        sfree (cb->capath);
        sfree (cb->clientkey);
        sfree (cb->clientcert);
        sfree (cb->clientkeypass);
        sfree (cb->send_buffer);

        sfree (cb);
}