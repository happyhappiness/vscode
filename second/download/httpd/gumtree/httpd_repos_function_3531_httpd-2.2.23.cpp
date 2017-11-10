int add_for_runtime(command_t *cmd_data)
{
    if (cmd_data->mode == mInstall) {
        return 0;
    }
    if (cmd_data->output == otDynamicLibraryOnly ||
        cmd_data->output == otLibrary) {
        FILE *f=fopen(cmd_data->fake_output_name,"w");
        if (f == NULL) {
            return -1;
        }
        fprintf(f,"%s\n", cmd_data->install_path);
        fclose(f);
        return(0);
    } else {
        return(ensure_fake_uptodate(cmd_data));
    }
}