    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t -D DUMP_MODULES : show all loaded modules ");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -M                 : a synonym for -t -D DUMP_MODULES");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t                 : run syntax check for config files");

    destroy_and_exit_process(process, 1);
}

int main(int argc, const char * const argv[])
{
