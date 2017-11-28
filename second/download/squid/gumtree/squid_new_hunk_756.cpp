        url = strstr(url, "//");

#if SHOULD_REJECT_UNKNOWN_URLS

        if (!url) {
            hp->request_parse_status = Http::scBadRequest;
            return conn->abortRequestParsing("error:invalid-request");
        }
#endif

        if (url)
            url = strchr(url + 2, '/');

