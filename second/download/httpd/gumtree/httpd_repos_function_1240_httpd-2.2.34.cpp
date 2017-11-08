static int mime_match(accept_rec *accept_r, var_rec *avail)
{
    const char *accept_type = accept_r->name;
    const char *avail_type = avail->mime_type;
    int len = strlen(accept_type);

    if ((len == 1 && accept_type[0] == '*')
            || (len == 3 && !strncmp(accept_type, "*/*", 3))) {
        /* Anything matches star or star/star */
        if (avail->mime_stars < 1) {
            avail->mime_stars = 1;
        }
        return 1;
    }
    else if (len > 2 && accept_type[len - 2] == '/'
                     && accept_type[len - 1] == '*'
                     && !strncmp(accept_type, avail_type, len - 2)
                     && avail_type[len - 2] == '/') {
        /* Any subtype matches for type/star */
        if (avail->mime_stars < 2) {
            avail->mime_stars = 2;
        }
        return 1;
    }
    else if (!strcmp(accept_type, avail_type)
             || (!strcmp(accept_type, "text/html")
                 && (!strcmp(avail_type, INCLUDES_MAGIC_TYPE)
                     || !strcmp(avail_type, INCLUDES_MAGIC_TYPE3)))) {
        if (accept_r->level >= avail->level) {
            avail->level_matched = avail->level;
            avail->mime_stars = 3;
            return 1;
        }
    }

    return OK;
}