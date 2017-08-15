{
                    fclose(configfile);
                    control_printf(SL_FAILURE, "421 Memory error while handling config file.");
                    exit(1);
                }