static void ap_ssi_get_tag_and_value(include_ctx_t *ctx, char **tag,
                                     char **tag_val, int dodecode)
{
    char *c = ctx->curr_tag_pos;
    int   shift_val = 0; 
    char  term = '\0';

    *tag_val = NULL;
    if (ctx->curr_tag_pos > ctx->combined_tag + ctx->tag_length) {
        *tag = NULL;
        return;
    }
    SKIP_TAG_WHITESPACE(c);
    *tag = c;             /* First non-whitespace character (could be NULL). */

    while (apr_islower(*c)) {
        c++;  /* Optimization for the common case where the tag */
    }         /* is already lowercase */

    while ((*c != '=') && (!apr_isspace(*c)) && (*c != '\0')) {
        *c = apr_tolower(*c);    /* find end of tag, lowercasing as we go... */
        c++;
    }

    if ((*c == '\0') || (**tag == '=')) {
        if ((**tag == '\0') || (**tag == '=')) {
            *tag = NULL;
        }
        ctx->curr_tag_pos = c;
        return;                      /* We have found the end of the buffer. */
    }                       /* We might have a tag, but definitely no value. */

    if (*c == '=') {
        *c++ = '\0'; /* Overwrite the '=' with a terminating byte after tag. */
    }
    else {                               /* Try skipping WS to find the '='. */
        *c++ = '\0';                                 /* Terminate the tag... */
        SKIP_TAG_WHITESPACE(c);
        
        /* There needs to be an equal sign if there's a value. */
        if (*c != '=') {
            ctx->curr_tag_pos = c;
            return; /* There apparently was no value. */
        }
        else {
            c++; /* Skip the equals sign. */
        }
    }

    SKIP_TAG_WHITESPACE(c);
    if (*c == '"' || *c == '\'' || *c == '`') { 
        /* Allow quoted values for space inclusion. 
         * NOTE: This does not pass the quotes on return.
         */
        term = *c++;
    }
    
    *tag_val = c;
    if (!term) {
        while (!apr_isspace(*c) && (*c != '\0')) {
            c++;
        }
    }
    else {
        while ((*c != term) && (*c != '\0') && (*c != '\\')) {
            /* Quickly scan past the string until we reach
             * either the end of the tag or a backslash.  If
             * we find a backslash, we have to switch to the
             * more complicated parser loop that follows.
             */
            c++;
        }
        if (*c == '\\') {
            do {
                /* Accept \" (or ' or `) as valid quotation of string. 
                 */
                if (*c == '\\') {  
                    /* Overwrite the "\" during the embedded 
                     * escape sequence of '"'. "\'" or '`'. 
                     * Shift bytes from here to next delimiter.     
                     */
                    c++;
                    if (*c == term) {
                        shift_val++;
                    }
                    if (shift_val > 0) {
                        *(c-shift_val) = *c;
                    }
                    if (*c == '\0') {
                        break;
                    }
                }

                c++;
                if (shift_val > 0) {
                    *(c-shift_val) = *c;
                }
            } while ((*c != term) && (*c != '\0'));
        }
    }
    
    *(c-shift_val) = '\0'; /* Overwrites delimiter (term or WS) with NULL. */
    ctx->curr_tag_pos = ++c;
    if (dodecode) {
        decodehtml(*tag_val);
    }

    return;
}