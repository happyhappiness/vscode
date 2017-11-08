static const char *set_speling(cmd_parms *cmd, void *mconfig, int arg)
{
    spconfig *cfg = (spconfig *) mconfig;

    cfg->enabled = arg;
    return NULL;
}