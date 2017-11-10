static void dav_append_prop(apr_pool_t *pool,
                            const char *name, const char *value,
                            apr_text_header *phdr)
{
    const char *s;
    const char *lang = value;

    /* skip past the xml:lang value */
    value += strlen(lang) + 1;

    if (*value == '\0') {
        /* the property is an empty value */
        if (*name == ':') {
            /* "no namespace" case */
            s = apr_psprintf(pool, "<%s/>" DEBUG_CR, name+1);
        }
        else {
            s = apr_psprintf(pool, "<ns%s/>" DEBUG_CR, name);
        }
    }
    else if (*lang != '\0') {
        if (*name == ':') {
            /* "no namespace" case */
            s = apr_psprintf(pool, "<%s xml:lang=\"%s\">%s</%s>" DEBUG_CR,
                             name+1, lang, value, name+1);
        }
        else {
            s = apr_psprintf(pool, "<ns%s xml:lang=\"%s\">%s</ns%s>" DEBUG_CR,
                             name, lang, value, name);
        }
    }
    else if (*name == ':') {
        /* "no namespace" case */
        s = apr_psprintf(pool, "<%s>%s</%s>" DEBUG_CR, name+1, value, name+1);
    }
    else {
        s = apr_psprintf(pool, "<ns%s>%s</ns%s>" DEBUG_CR, name, value, name);
    }

    apr_text_append(pool, phdr, s);
}