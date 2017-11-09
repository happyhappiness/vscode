int h2_config_geti(const h2_config *conf, h2_config_var_t var)
{
    return (int)h2_config_geti64(conf, var);
}