int main(int argc, char *argv[])
{
    int rc;
    command_t cmd_data;

    memset(&cmd_data, 0, sizeof(cmd_data));

    cmd_data.options.pic_mode = pic_UNKNOWN;

    cmd_data.program_opts = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cmd_data.program_opts);
    cmd_data.arglist = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cmd_data.arglist);
    cmd_data.tmp_dirs = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cmd_data.tmp_dirs);
    cmd_data.obj_files = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cmd_data.obj_files);
    cmd_data.dep_rpaths = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cmd_data.dep_rpaths);
    cmd_data.rpaths = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cmd_data.rpaths);
    cmd_data.static_opts.normal = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cmd_data.static_opts.normal);
    cmd_data.shared_opts.normal = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cmd_data.shared_opts.normal);
    cmd_data.shared_opts.dependencies = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cmd_data.shared_opts.dependencies);

    cmd_data.mode = mUnknown;
    cmd_data.output = otGeneral;

    parse_args(argc, argv, &cmd_data);
    post_parse_fixup(&cmd_data);

    if (cmd_data.mode == mUnknown) {
        exit(0);
    }

    rc = run_mode(&cmd_data);

    if (!rc) {
       add_for_runtime(&cmd_data); 
    }

    cleanup_tmp_dirs(&cmd_data);
    return rc;
}