apr_file_printf(out, "Mutex %s: dir=\"%s\" mechanism=%s %s\n", name, dir, mech,
                        mxcfg->omit_pid ? "[OmitPid]" : "");