static const char *cmd_rewriterule_setflag(apr_pool_t *p, void *_cfg,
                                           char *key, char *val)
{
    rewriterule_entry *cfg = _cfg;
    int error = 0;

    switch (*key++) {
    case 'b':
    case 'B':
        if (!*key || !strcasecmp(key, "ackrefescaping")) {
            cfg->flags |= RULEFLAG_ESCAPEBACKREF;
        }
        else {
            ++error;
        }
        break;
    case 'c':
    case 'C':
        if (!*key || !strcasecmp(key, "hain")) {           /* chain */
            cfg->flags |= RULEFLAG_CHAIN;
        }
        else if (((*key == 'O' || *key == 'o') && !key[1])
                 || !strcasecmp(key, "ookie")) {           /* cookie */
            data_item *cp = cfg->cookie;

            if (!cp) {
                cp = cfg->cookie = apr_palloc(p, sizeof(*cp));
            }
            else {
                while (cp->next) {
                    cp = cp->next;
                }
                cp->next = apr_palloc(p, sizeof(*cp));
                cp = cp->next;
            }

            cp->next = NULL;
            cp->data = val;
        }
        else {
            ++error;
        }
        break;
    case 'd':
    case 'D':
        if (!*key || !strcasecmp(key, "PI") || !strcasecmp(key,"iscardpath")) {
            cfg->flags |= (RULEFLAG_DISCARDPATHINFO);
        }
        break;
    case 'e':
    case 'E':
        if (!*key || !strcasecmp(key, "nv")) {             /* env */
            data_item *cp = cfg->env;

            if (!cp) {
                cp = cfg->env = apr_palloc(p, sizeof(*cp));
            }
            else {
                while (cp->next) {
                    cp = cp->next;
                }
                cp->next = apr_palloc(p, sizeof(*cp));
                cp = cp->next;
            }

            cp->next = NULL;
            cp->data = val;
        }
        else if (!strcasecmp(key, "nd")) {                /* end */
            cfg->flags |= RULEFLAG_END;
        }
        else {
            ++error;
        }
        break;

    case 'f':
    case 'F':
        if (!*key || !strcasecmp(key, "orbidden")) {       /* forbidden */
            cfg->flags |= (RULEFLAG_STATUS | RULEFLAG_NOSUB);
            cfg->forced_responsecode = HTTP_FORBIDDEN;
        }
        else {
            ++error;
        }
        break;

    case 'g':
    case 'G':
        if (!*key || !strcasecmp(key, "one")) {            /* gone */
            cfg->flags |= (RULEFLAG_STATUS | RULEFLAG_NOSUB);
            cfg->forced_responsecode = HTTP_GONE;
        }
        else {
            ++error;
        }
        break;

    case 'h':
    case 'H':
        if (!*key || !strcasecmp(key, "andler")) {         /* handler */
            cfg->forced_handler = val;
        }
        else {
            ++error;
        }
        break;
    case 'l':
    case 'L':
        if (!*key || !strcasecmp(key, "ast")) {            /* last */
            cfg->flags |= RULEFLAG_LASTRULE;
        }
        else {
            ++error;
        }
        break;

    case 'n':
    case 'N':
        if (((*key == 'E' || *key == 'e') && !key[1])
            || !strcasecmp(key, "oescape")) {              /* noescape */
            cfg->flags |= RULEFLAG_NOESCAPE;
        }
        else if (!*key || !strcasecmp(key, "ext")) {       /* next */
            cfg->flags |= RULEFLAG_NEWROUND;
            if (val && *val) { 
                cfg->maxrounds = atoi(val);
            }

        }
        else if (((*key == 'S' || *key == 's') && !key[1])
            || !strcasecmp(key, "osubreq")) {              /* nosubreq */
            cfg->flags |= RULEFLAG_IGNOREONSUBREQ;
        }
        else if (((*key == 'C' || *key == 'c') && !key[1])
            || !strcasecmp(key, "ocase")) {                /* nocase */
            cfg->flags |= RULEFLAG_NOCASE;
        }
        else {
            ++error;
        }
        break;

    case 'p':
    case 'P':
        if (!*key || !strcasecmp(key, "roxy")) {           /* proxy */
            cfg->flags |= RULEFLAG_PROXY;
        }
        else if (((*k