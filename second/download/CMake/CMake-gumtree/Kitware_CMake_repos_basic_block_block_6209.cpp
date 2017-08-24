f(path_q_sep) {
      /* according to rfc3986, allow the query (?foo=bar)
         also on protocols that can't handle it.

         cut the string-part after '?'
      */

      /* terminate the string */
      path_q_sep[0] = 0;
    }