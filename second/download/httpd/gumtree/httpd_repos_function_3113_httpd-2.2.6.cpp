void cleanup_tmp_dirs(cmd_data_t *cmd_data)
{
    int d;

    for (d=0; d < cmd_data->num_tmp_dirs; d++) {
        cleanup_tmp_dir(cmd_data->tmp_dirs[d]);
    }
}