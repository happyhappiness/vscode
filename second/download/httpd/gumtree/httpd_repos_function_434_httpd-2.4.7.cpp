static char *parse_log_item(apr_pool_t *p, log_format_item *it, const char **sa)
{
    const char *s = *sa;
    ap_log_handler *handler;

    if (*s != '%') {
        return parse_log_misc_string(p, it, sa);
    }

    ++s;
    it->condition_sense = 0;
    it->conditions = NULL;

    if (*s == '%') {
        it->arg = "%";
        it->func = constant_item;
        *sa = ++s;

        return NULL;
    }

    it->want_orig = -1;
    it->arg = "";               /* For safety's sake... */

    while (*s) {
        int i;

        switch (*s) {
        case '!':
            ++s;
            it->condition_sense = !it->condition_sense;
            break;

        case '<':
            ++s;
            it->want_orig = 1;
            break;

        case '>':
            ++s;
            it->want_orig = 0;
            break;

        case ',':
            ++s;
            break;

        case '{':
            ++s;
            it->arg = ap_getword(p, &s, '}');
            break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            i = *s - '0';
            while (apr_isdigit(*++s)) {
                i = i * 10 + (*s) - '0';
            }
            if (!it->conditions) {
                it->conditions = apr_array_make(p, 4, sizeof(int));
            }
            *(int *) apr_array_push(it->conditions) = i;
            break;

        default:
            handler = (ap_log_handler *)apr_hash_get(log_hash, s++, 1);
            if (!handler) {
                char dummy[2];

                dummy[0] = s[-1];
                dummy[1] = '\0';
                return apr_pstrcat(p, "Unrecognized LogFormat directive %",
                               dummy, NULL);
            }
            it->func = handler->func;
            if (it->want_orig == -1) {
                it->want_orig = handler->want_orig_default;
            }
            *sa = s;
            return NULL;
        }
    }

    return "Ran off end of LogFormat parsing args to some directive";
}