static const char *cmd_rewritebase(cmd_parms *cmd, void *in_dconf,
                                   const char *a1)
{
    rewrite_perdir_conf *dconf = in_dconf;

    if (cmd->path == NULL || dconf == NULL) {
        return "RewriteBase: only valid in per-directory config files";
    }
    if (a1[0] == '\0') {
        return "RewriteBase: empty URL not allowed";
    }
    if (a1[0] != '/') {
        return "RewriteBase: argument is not a valid URL";
    }

    dconf->baseurl = a1;

    return NULL;
}