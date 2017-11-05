static const char *
cmd_modem_standard(cmd_parms *cmd,
             void *dconf,
             const char *input)
{
    const modem_speed_t *standard;
    int i = 0;
    dialup_dcfg_t *dcfg = (dialup_dcfg_t*)dconf;
    
    dcfg->bytes_per_second = 0;

    while (modem_bitrates[i].name != NULL) {
        standard = &modem_bitrates[i];
        if (strcasecmp(standard->name, input) == 0) {
            dcfg->bytes_per_second = standard->bytes_per_second;
            break;
        }
        i++;
    }

    if (dcfg->bytes_per_second == 0) {
        return "mod_diaulup: Unkonwn Modem Standard specified.";
    }

    return NULL;
}