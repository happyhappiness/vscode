int main(int argc, char *argv[])
{
    int rc;
    cmd_data_t cmd_data;

    memset(&cmd_data, 0, sizeof(cmd_data));
    cmd_data.mode = mCompile;
    cmd_data.output_type = otGeneral;

    parse_args(argc, argv, &cmd_data);
    rc = execute_command(&cmd_data);

    if (rc == 0 && cmd_data.stub_name) {
        fopen(cmd_data.stub_name, "w");
    }

    cleanup_tmp_dirs(&cmd_data);
    return rc;
}