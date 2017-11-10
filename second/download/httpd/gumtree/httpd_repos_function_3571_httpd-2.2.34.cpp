void post_parse_fixup(command_t *cmd_data)
{
    switch (cmd_data->mode)
    {
    case mCompile:
#ifdef PIC_FLAG
        if (cmd_data->options.pic_mode != pic_AVOID) {
            push_count_chars(cmd_data->arglist, PIC_FLAG);
        }
#endif
        if (cmd_data->output_name) {
            push_count_chars(cmd_data->arglist, "-o");
            push_count_chars(cmd_data->arglist, cmd_data->output_name);
        }
        break;
    case mLink:
        link_fixup(cmd_data);
        break;
    case mInstall:
        if (cmd_data->output == otLibrary) {
            link_fixup(cmd_data);
        }
    default:
        break;
    }

#if USE_OMF
    if (cmd_data->output == otObject ||
        cmd_data->output == otProgram ||
        cmd_data->output == otLibrary ||
        cmd_data->output == otDynamicLibraryOnly) {
        push_count_chars(cmd_data->arglist, "-Zomf");
    }
#endif

    if (cmd_data->options.shared &&
            (cmd_data->output == otObject ||
             cmd_data->output == otLibrary ||
             cmd_data->output == otDynamicLibraryOnly)) {
#ifdef SHARE_SW
        push_count_chars(cmd_data->arglist, SHARE_SW);
#endif
    }
}