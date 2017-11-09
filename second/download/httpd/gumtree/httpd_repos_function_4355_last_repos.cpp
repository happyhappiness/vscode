static void setup_signal_names(char *prefix)
{
    apr_snprintf(signal_name_prefix, sizeof(signal_name_prefix), prefix);
    apr_snprintf(signal_shutdown_name, sizeof(signal_shutdown_name),
        "%s_shutdown", signal_name_prefix);
    apr_snprintf(signal_restart_name, sizeof(signal_restart_name),
        "%s_restart", signal_name_prefix);
}