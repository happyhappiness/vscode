static int wh_callback_init (wh_callback_t *cb) /* {{{ */
{
        if (cb->curl != NULL)
                return (0);

        cb->curl = curl_easy_init ();
        if (cb->curl == NULL)
        {
                ERROR ("curl plugin: curl_easy_init failed.");
                return (-1);
        }

        if (cb->low_speed_limit > 0 && cb->low_speed_time > 0)
        {
                curl_easy_setopt (cb->curl, CURLOPT_LOW_SPEED_LIMIT,
                                  (long) (cb->low_speed_limit * cb->low_speed_time));
                curl_easy_setopt (cb->curl, CURLOPT_LOW_SPEED_TIME,
                                  (long) cb->low_speed_time);
        }

#ifdef HAVE_CURLOPT_TIMEOUT_MS
        if (cb->timeout > 0)
                curl_easy_setopt (cb->curl, CURLOPT_TIMEOUT_MS, (long) cb->timeout);
#endif

        curl_easy_setopt (cb->curl, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt (cb->curl, CURLOPT_USERAGENT, COLLECTD_USERAGENT);

        cb->headers = curl_slist_append (cb->headers, "Accept:  */*");
        if (cb->format == WH_FORMAT_JSON || cb->format == WH_FORMAT_KAIROSDB)
                cb->headers = curl_slist_append (cb->headers, "Content-Type: application/json");
        else
                cb->headers = curl_slist_append (cb->headers, "Content-Type: text/plain");
        cb->headers = curl_slist_append (cb->headers, "Expect:");
        curl_easy_setopt (cb->curl, CURLOPT_HTTPHEADER, cb->headers);

        curl_easy_setopt (cb->curl, CURLOPT_ERRORBUFFER, cb->curl_errbuf);
        curl_easy_setopt (cb->curl, CURLOPT_URL, cb->location);
        curl_easy_setopt (cb->curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt (cb->curl, CURLOPT_MAXREDIRS, 50L);

        if (cb->user != NULL)
        {
#ifdef HAVE_CURLOPT_USERNAME
                curl_easy_setopt (cb->curl, CURLOPT_USERNAME, cb->user);
                curl_easy_setopt (cb->curl, CURLOPT_PASSWORD,
                        (cb->pass == NULL) ? "" : cb->pass);
#else
                size_t credentials_size;

                credentials_size = strlen (cb->user) + 2;
                if (cb->pass != NULL)
                        credentials_size += strlen (cb->pass);

                cb->credentials = malloc (credentials_size);
                if (cb->credentials == NULL)
                {
                        ERROR ("curl plugin: malloc failed.");
                        return (-1);
                }

                ssnprintf (cb->credentials, credentials_size, "%s:%s",
                                cb->user, (cb->pass == NULL) ? "" : cb->pass);
                curl_easy_setopt (cb->curl, CURLOPT_USERPWD, cb->credentials);
#endif
                curl_easy_setopt (cb->curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        }

        curl_easy_setopt (cb->curl, CURLOPT_SSL_VERIFYPEER, (long) cb->verify_peer);
        curl_easy_setopt (cb->curl, CURLOPT_SSL_VERIFYHOST,
                        cb->verify_host ? 2L : 0L);
        curl_easy_setopt (cb->curl, CURLOPT_SSLVERSION, cb->sslversion);
        if (cb->cacert != NULL)
                curl_easy_setopt (cb->curl, CURLOPT_CAINFO, cb->cacert);
        if (cb->capath != NULL)
                curl_easy_setopt (cb->curl, CURLOPT_CAPATH, cb->capath);

        if (cb->clientkey != NULL && cb->clientcert != NULL)
        {
            curl_easy_setopt (cb->curl, CURLOPT_SSLKEY, cb->clientkey);
            curl_easy_setopt (cb->curl, CURLOPT_SSLCERT, cb->clientcert);

            if (cb->clientkeypass != NULL)
                curl_easy_setopt (cb->curl, CURLOPT_SSLKEYPASSWD, cb->clientkeypass);
        }

        wh_reset_buffer (cb);

        return (0);
}