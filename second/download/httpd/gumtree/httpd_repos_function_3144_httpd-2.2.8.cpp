int ensure_fake_uptodate(command_t *cmd_data)
{
    /* FIXME: could do the stat/touch here, but nah... */
    const char *touch_args[3];

    if (cmd_data->mode == mInstall) {
        return 0;
    }

    touch_args[0] = "touch";
    touch_args[1] = cmd_data->fake_output_name;
    touch_args[2] = NULL;
    return external_spawn(cmd_data, "touch", touch_args);
}