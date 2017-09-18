                 "  -L                : list available configuration "
                 "directives");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t -D DUMP_VHOSTS : show parsed settings (currently only "
                 "vhost settings)");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -S                : a synonym for -t -D DUMP_VHOSTS");   
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t                : run syntax check for config files");

    destroy_and_exit_process(process, 1);
}

int main(int argc, const char * const argv[])
