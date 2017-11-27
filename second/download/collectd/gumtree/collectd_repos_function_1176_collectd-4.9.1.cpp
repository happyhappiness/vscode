static int wh_callback_init (wh_callback_t *cb) /* {{{ */
{
        struct curl_slist *headers;

        if (cb->curl != NULL)
                return (0);

        cb->curl = curl_easy_init ();
        if (cb->curl == NULL)
        {
                ERROR ("curl plugin: curl_easy_init failed.");
                return (-1);
        }

        curl_easy_setopt (cb->curl, CURLOPT_USERAGENT, PACKAGE_NAME"/"PACKAGE_VERSION);

        headers = NULL;
        headers = curl_slist_append (headers, "Accept:  */*");
        if (cb->format == WH_FORMAT_JSON)
                headers = curl_slist_append (headers, "Content-Type: application/json");
        else
                headers = curl_slist_append (headers, "Content-Type: text/plain");
        headers = curl_slist_append (headers, "Expect:");
        curl_easy_setopt (cb->curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt (cb->curl, CURLOPT_ERRORBUFFER, cb->curl_errbuf);
        curl_easy_setopt (cb->curl, CURLOPT_URL, cb->location);

        if (cb->user != NULL)
        {
                size_t credentials_size;

                credentials_size = strlen (cb->user) + 2;
                if (cb->pass != NULL)
                        credentials_size += strlen (cb->pass);

                cb->credentials = (char *) malloc (credentials_size);
                if (cb->credentials == NULL)
                {
                        ERROR ("curl plugin: malloc failed.");
                        return (-1);
                }

                ssnprintf (cb->credentials, credentials_size, "%s:%s",
                                cb->user, (cb->pass == NULL) ? "" : cb->pass);
                curl_easy_setopt (cb->curl, CURLOPT_USERPWD, cb->credentials);
                curl_easy_setopt (cb->curl, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
        }

        curl_easy_setopt (cb->curl, CURLOPT_SSL_VERIFYPEER, cb->verify_peer);
        curl_easy_setopt (cb->curl, CURLOPT_SSL_VERIFYHOST,
                        cb->verify_host ? 2 : 0);
        if (cb->cacert != NULL)
                curl_easy_setopt (cb->curl, CURLOPT_CAINFO, cb->cacert);

        wh_reset_buffer (cb);

        return (0);
}