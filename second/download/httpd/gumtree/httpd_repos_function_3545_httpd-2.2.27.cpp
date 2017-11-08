void cleanup_tmp_dirs(command_t *cmd_data)
{
    int d;

    for (d = 0; d < cmd_data->tmp_dirs->num; d++) {
        cleanup_tmp_dir(cmd_data->tmp_dirs->vals[d]);
    }
}