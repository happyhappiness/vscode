r(tok_end = tok_start; tok_end < no_proxy_len &&
            strchr(separator, no_proxy[tok_end]) == NULL; ++tok_end)
        /* Look for the end of the token. */
        ;