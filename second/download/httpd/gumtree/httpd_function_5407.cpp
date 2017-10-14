void ap_mpm_dump_pidfile(apr_pool_t *p, apr_file_t *out)
{
    apr_file_printf(out, "PidFile: \"%s\"\n",
                    ap_server_root_relative(p, ap_pid_fname));
}