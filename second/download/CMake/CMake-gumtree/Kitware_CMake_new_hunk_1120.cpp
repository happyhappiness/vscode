  return TRUE; /* OK, proceed */
}

#ifdef CURLRES_SYNCH /* the functions below are for synchronous resolves */

/*
 * Curl_getaddrinfo() - the ipv4 synchronous version.
 *
 * The original code to this function was from the Dancer source code, written
 * by Bjorn Reese, it has since been patched and modified considerably.
 *
 * gethostbyname_r() is the thread-safe version of the gethostbyname()
 * function. When we build for plain IPv4, we attempt to use this
