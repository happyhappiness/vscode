static int alias_match(const char *uri, const char *alias_fakename)
{
    const char *end_fakename = alias_fakename + strlen(alias_fakename);
    const char *aliasp = alias_fakename, *urip = uri;
    const char *end_uri = uri + strlen(uri);

    while (aliasp < end_fakename && urip < end_uri) {
        if (*aliasp == '/') {
            /* any number of '/' in the alias matches any number in
             * the supplied URI, but there must be at least one...
             */
            if (*urip != '/')
                return 0;

            while (*aliasp == '/')
                ++aliasp;
            while (*urip == '/')
                ++urip;
        }
        else {
            /* Other characters are compared literally */
            if (*urip++ != *aliasp++)
                return 0;
        }
    }

    /* fixup badly encoded stuff (e.g. % as last character) */
    if (aliasp > end_fakename) {
        aliasp = end_fakename;
    }
    if (urip > end_uri) {
        urip = end_uri;
    }

   /* We reach the end of the uri before the end of "alias_fakename"
    * for example uri is "/" and alias_fakename "/examples"
    */
   if (urip == end_uri && aliasp != end_fakename) {
       return 0;
   }

    /* Check last alias path component matched all the way */
    if (aliasp[-1] != '/' && *urip != '\0' && *urip != '/')
        return 0;

    /* Return number of characters from URI which matched (may be
     * greater than length of alias, since we may have matched
     * doubled slashes)
     */

    return urip - uri;
}