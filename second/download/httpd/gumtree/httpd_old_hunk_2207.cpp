            cmd_data->mode = mInstall;
        }
    } else if (strcmp(var, "shared") == 0) {
        if (cmd_data->mode == mLink) {
            cmd_data->output = otDynamicLibraryOnly;
        }
        cmd_data->options.shared = 1;
    } else if (strcmp(var, "export-all") == 0) {
        cmd_data->options.export_all = 1;
    } else if (strcmp(var, "dry-run") == 0) {
        printf("Dry-run mode on!\n");
        cmd_data->options.dry_run = 1;
    } else if (strcmp(var, "version") == 0) {
