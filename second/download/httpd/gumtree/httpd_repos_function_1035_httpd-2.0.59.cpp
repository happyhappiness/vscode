static const char *set_force_priority(cmd_parms *cmd, void *n_, const char *w)
{
    neg_dir_config *n = n_;

    if (!strcasecmp(w, "None")) {
        if (n->forcelangpriority & ~FLP_NONE) {
            return "Cannot combine ForceLanguagePriority options with None";
        }
        n->forcelangpriority = FLP_NONE;
    }
    else if (!strcasecmp(w, "Prefer")) {
        if (n->forcelangpriority & FLP_NONE) {
            return "Cannot combine ForceLanguagePriority options None and "
                   "Prefer";
        }
        n->forcelangpriority |= FLP_PREFER;
    }
    else if (!strcasecmp(w, "Fallback")) {
        if (n->forcelangpriority & FLP_NONE) {
            return "Cannot combine ForceLanguagePriority options None and "
                   "Fallback";
        }
        n->forcelangpriority |= FLP_FALLBACK;
    }
    else {
        return apr_pstrcat(cmd->pool, "Invalid ForceLanguagePriority option ",
                           w, NULL);
    }

    return NULL;
}