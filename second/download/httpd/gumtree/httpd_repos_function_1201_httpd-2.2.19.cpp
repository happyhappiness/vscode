static const char *fake_rewritelog(cmd_parms *cmd, void *dummy, const char *a1)
{
    return "RewriteLog and RewriteLogLevel are not supported by this build "
           "of mod_rewrite because it was compiled using the "
           "-DREWRITELOG_DISABLED compiler option. You have to recompile "
           "mod_rewrite WITHOUT this option in order to use the rewrite log.";
}