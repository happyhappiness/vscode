static void strip_paren_comments(char *hdr)
{
    /* Hmmm... is this correct?  In Roy's latest draft, (comments) can nest! */
    /* Nope, it isn't correct.  Fails to handle backslash escape as well.    */

    while (*hdr) {
        if (*hdr == '"') {
            hdr = strchr(hdr, '"');
            if (hdr == NULL) {
                return;
            }
            ++hdr;
        }
        else if (*hdr == '(') {
            while (*hdr && *hdr != ')') {
                *hdr++ = ' ';
            }

            if (*hdr) {
                *hdr++ = ' ';
            }
        }
        else {
            ++hdr;
        }
    }
}