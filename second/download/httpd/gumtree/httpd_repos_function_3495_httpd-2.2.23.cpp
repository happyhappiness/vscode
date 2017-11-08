int run_command(command_t *cmd_data, count_chars *cc)
{
    char *command;
    const char *spawn_args[4];
    count_chars tmpcc;

    init_count_chars(&tmpcc);

    if (cmd_data->program) {
        push_count_chars(&tmpcc, cmd_data->program);
    }

    append_count_chars(&tmpcc, cmd_data->program_opts);

    append_count_chars(&tmpcc, cc);

    command = shell_esc(flatten_count_chars(&tmpcc, 1));

    spawn_args[0] = SHELL_CMD;
    spawn_args[1] = "-c";
    spawn_args[2] = command;
    spawn_args[3] = NULL;
    return external_spawn(cmd_data, spawn_args[0], (const char**)spawn_args);
}