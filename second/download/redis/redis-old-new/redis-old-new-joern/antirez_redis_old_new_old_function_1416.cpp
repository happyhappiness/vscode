static void json_set_number_precision(json_config_t *cfg, int prec)
{
    cfg->encode_number_precision = prec;
    sprintf(cfg->number_fmt, "%%.%dg", prec);
}