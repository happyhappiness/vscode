void link_fixup(command_t *c)
{
    /* If we were passed an -rpath directive, we need to build
     * shared objects too.  Otherwise, we should only create static
     * libraries.
     */
    if (!c->install_path && (c->output == otDynamicLibraryOnly ||
        c->output == otModule || c->output == otLibrary)) {
        c->output = otStaticLibraryOnly;
    }

    if (c->output == otDynamicLibraryOnly ||
        c->output == otModule ||
        c->output == otLibrary) {

        push_count_chars(c->shared_opts.normal, "-o");
        if (c->output == otModule) {
            push_count_chars(c->shared_opts.normal, c->module_name.normal);
        }
        else {
            char *tmp;
            push_count_chars(c->shared_opts.normal, c->shared_name.normal);
#ifdef DYNAMIC_INSTALL_NAME
            push_count_chars(c->shared_opts.normal, DYNAMIC_INSTALL_NAME);

            tmp = (char*)malloc(PATH_MAX);
            strcat(tmp, c->install_path);
            strcat(tmp, strrchr(c->shared_name.normal, '/'));
            push_count_chars(c->shared_opts.normal, tmp);
#endif
        }

        append_count_chars(c->shared_opts.normal, c->obj_files);
        append_count_chars(c->shared_opts.normal, c->shared_opts.dependencies);

        if (c->options.export_all) {
#ifdef GEN_EXPORTS
            generate_def_file(c);
#endif
        }
    }

    if (c->output == otLibrary || c->output == otStaticLibraryOnly) {
        push_count_chars(c->static_opts.normal, "-o");
        push_count_chars(c->static_opts.normal, c->output_name);
    }

    if (c->output == otProgram) {
        if (c->output_name) {
            push_count_chars(c->arglist, "-o");
            push_count_chars(c->arglist, c->output_name);
            append_count_chars(c->arglist, c->obj_files);
            append_count_chars(c->arglist, c->shared_opts.dependencies);
            add_dynamic_link_opts(c, c->arglist);
        }
    }
}