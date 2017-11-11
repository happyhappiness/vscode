void parse_args(int argc, char *argv[], cmd_data_t *cmd_data)
{
    int a;
    char *arg;
    bool argused;

    for (a=1; a < argc; a++) {
        arg = argv[a];
        argused = false;

        if (arg[0] == '-') {
            if (arg[1] == '-') {
                argused = parse_long_opt(arg + 2, cmd_data);
            } else if (arg[1] == 'o' && a+1 < argc) {
                cmd_data->arglist[cmd_data->num_args++] = arg;
                arg = argv[++a];
                argused = parse_output_file_name(arg, cmd_data);
            } else {
                int num_used = parse_short_opt(arg + 1, cmd_data);
                argused = num_used > 0;

                if (num_used > 1) {
                    a += num_used - 1;
                }
            }
        } else {
            argused = parse_input_file_name(arg, cmd_data);
        }

        if (!argused) {
            cmd_data->arglist[cmd_data->num_args++] = arg;
        }
    }

    post_parse_fixup(cmd_data);
}