int parse_output_file_name(char *arg, command_t *cmd_data)
{
    char *name = strrchr(arg, '/');
    char *ext = strrchr(arg, '.');
    char *newarg = NULL;
    int pathlen;

    cmd_data->fake_output_name = arg;

    if (name) {
        name++;
    }
    else {
        name = strrchr(arg, '\\');

        if (name == NULL) {
            name = arg;
        }
        else {
            name++;
        }
    }

#ifdef EXE_EXT
    if (!ext || strcmp(ext, EXE_EXT) == 0) {
#else
    if (!ext) {
#endif
        cmd_data->basename = arg;
        cmd_data->output = otProgram;
#if defined(_OSD_POSIX)
        cmd_data->options.pic_mode = pic_AVOID;
#endif
        newarg = (char *)malloc(strlen(arg) + 5);
        strcpy(newarg, arg);
#ifdef EXE_EXT
	if (!ext) {
        strcat(newarg, EXE_EXT);
	}
#endif
        cmd_data->output_name = newarg;
        return 1;
    }

    ext++;
    pathlen = name - arg;

    if (strcmp(ext, "la") == 0) {
        assert(cmd_data->mode == mLink);

        cmd_data->basename = arg;
        cmd_data->static_name.normal = gen_library_name(arg, 0);
        cmd_data->shared_name.normal = gen_library_name(arg, 1);
        cmd_data->module_name.normal = gen_library_name(arg, 2);
        cmd_data->static_name.install = gen_install_name(arg, 0);
        cmd_data->shared_name.install = gen_install_name(arg, 1);
        cmd_data->module_name.install = gen_install_name(arg, 2);

#ifdef TRUNCATE_DLL_NAME
        if (shared) {
          arg = truncate_dll_name(arg);
        }
#endif

        cmd_data->output_name = arg;
        return 1;
    }

    if (strcmp(ext, "lo") == 0) {
        cmd_data->basename = arg;
        cmd_data->output = otObject;
        newarg = (char *)malloc(strlen(arg) + 2);
        strcpy(newarg, arg);
        ext = strrchr(newarg, '.') + 1;
        strcpy(ext, OBJECT_EXT);
        cmd_data->output_name = newarg;
        return 1;
    }

    return 0;
}

void parse_args(int argc, char *argv[], command_t *cmd_data)
{
    int a;
    char *arg;
    int argused;

    for (a = 1; a < argc; a++) {
        arg = argv[a];
        argused = 1;

        if (arg[0] == '-') {
            if (arg[1] == '-') {
                argused = parse_long_opt(arg + 2, cmd_data);
            }
            else {
                argused = parse_short_opt(arg + 1, cmd_data);
            }

            /* We haven't done anything with it yet, try some of the
             * more complicated short opts... */
            if (argused == 0 && a + 1 < argc) {
                if (arg[1] == 'o' && !arg[2]) {
                    arg = argv[++a];
                    argused = parse_output_file_name(arg, cmd_data);
                } else if (strcmp(arg+1, "MT") == 0) {
                    if (!cmd_data->options.silent) {
                        printf("Adding: %s\n", arg);
                    }
                    push_count_chars(cmd_data->arglist, arg);
                    arg = argv[++a];
                    if (!cmd_data->options.silent) {
                        printf(" %s\n", arg);
                    }
                    push_count_chars(cmd_data->arglist, arg);
                    argused = 1;
                } else if (strcmp(arg+1, "rpath") == 0) {
                    /* Aha, we should try to link both! */
                    cmd_data->install_path = argv[++a];
                    argused = 1;
                } else if (strcmp(arg+1, "release") == 0) {
                    /* Store for later deciphering */
                    cmd_data->version_info = argv[++a];
                    argused = 1;
                } else if (strcmp(arg+1, "version-info") == 0) {
                    /* Store for later deciphering */
                    cmd_data->version_info = argv[++a];
                    argused = 1;
                } else if (strcmp(arg+1, "export-symbols-regex") == 0) {
                    /* Skip the argument. */
                    ++a;
                    argused = 1;
                } else if (strcmp(arg+1, "release") == 0) {
                    /* Skip the argument. */
                    ++a;
                    argused = 1;
                } else if (strcmp(arg+1, "undefined") == 0) {
                    cmd_data->undefined_flag = argv[++a];
                    argused = 1;
                } else if (arg[1] == 'R' && !arg[2]) {
                    /* -R dir Add dir to runtime library search path. */
                    add_runtimedirlib(argv[++a], cmd_data);
                    argused = 1;
                }
            }
        } else {
            argused = parse_input_file_name(arg, cmd_data);
        }

        if (!argused) {
            if (!cmd_data->options.silent) {
                printf("Adding: %s\n", arg);
            }
            push_count_chars(cmd_data->arglist, arg);
        }
    }

}

#ifdef GEN_EXPORTS
void generate_def_file(command_t *cmd_data)
{
    char def_file[1024];
    char implib_file[1024];
    char *ext;
    FILE *hDef;
    char *export_args[1024];
    int num_export_args = 0;
    char *cmd;
    int cmd_size = 0;
    int a;

    if (cmd_data->output_name) {
        strcpy(def_file, cmd_data->output_name);
        strcat(def_file, ".def");
        hDef = fopen(def_file, "w");

        if (hDef != NULL) {
            fprintf(hDef, "LIBRARY '%s' INITINSTANCE\n", nameof(cmd_data->output_name));
            fprintf(hDef, "DATA NONSHARED\n");
            fprintf(hDef, "EXPORTS\n");
            fclose(hDef);

            for (a = 0; a < cmd_data->num_obj_files; a++) {
                cmd_size += strlen(cmd_data->obj_files[a]) + 1;
            }

            cmd_size += strlen(GEN_EXPORTS) + strlen(def_file) + 3;
            cmd = (char *)malloc(cmd_size);
            strcpy(cmd, GEN_EXPORTS);

            for (a=0; a < cmd_data->num_obj_files; a++) {
                strcat(cmd, " ");
                strcat(cmd, cmd_data->obj_files[a] );
            }

            strcat(cmd, ">>");
            strcat(cmd, def_file);
            puts(cmd);
            export_args[num_export_args++] = SHELL_CMD;
            export_args[num_export_args++] = "-c";
            export_args[num_export_args++] = cmd;
            export_args[num_export_args++] = NULL;
            external_spawn(cmd_data, export_args[0], (const char**)export_args);
            cmd_data->arglist[cmd_data->num_args++] = strdup(def_file);

            /* Now make an import library for the dll */
            num_export_args = 0;
            export_args[num_export_args++] = DEF2IMPLIB_CMD;
            export_args[num_export_args++] = "-o";

            strcpy(implib_file, ".libs/");
            strcat(implib_file, cmd_data->basename);
            ext = strrchr(implib_file, '.');

            if (ext)
                *ext = 0;

            strcat(implib_file, ".");
            strcat(implib_file, STATIC_LIB_EXT);

            export_args[num_export_args++] = implib_file;
            export_args[num_export_args++] = def_file;
            export_args[num_export_args++] = NULL;
            external_spawn(cmd_data, export_args[0], (const char**)export_args);

        }
    }
}
#endif

const char* expand_path(const char *relpath)
{
    char foo[PATH_MAX], *newpath;

    getcwd(foo, PATH_MAX-1);
    newpath = (char*)malloc(strlen(foo)+strlen(relpath)+2);
    strcat(newpath, foo);
    strcat(newpath, "/");
    strcat(newpath, relpath);
    return newpath;
}

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

int run_mode(command_t *cmd_data)
{
    int rv;
    count_chars *cctemp;

    cctemp = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cctemp);

    switch (cmd_data->mode)
    {
    case mCompile:
        rv = run_command(cmd_data, cmd_data->arglist);
        if (rv) {
            return rv;
        }
        break;
    case mInstall:
        /* Well, we'll assume it's a file going to a directory... */
        /* For brain-dead install-sh based scripts, we have to repeat
         * the command N-times.  install-sh should die.
         */
        if (!cmd_data->output_name) {
            rv = run_command(cmd_data, cmd_data->arglist);
            if (rv) {
                return rv;
            }
        }
        if (cmd_data->output_name) {
            append_count_chars(cctemp, cmd_data->arglist);
            insert_count_chars(cctemp,
                               cmd_data->output_name,
                               cctemp->num - 1);
            rv = run_command(cmd_data, cctemp);
            if (rv) {
                return rv;
            }
            clear_count_chars(cctemp);
        }
        if (cmd_data->static_name.install) {
            append_count_chars(cctemp, cmd_data->arglist);
            insert_count_chars(cctemp,
                               cmd_data->static_name.install,
                               cctemp->num - 1);
            rv = run_command(cmd_data, cctemp);
            if (rv) {
                return rv;
            }
#if defined(__APPLE__) && defined(RANLIB)
            /* From the Apple libtool(1) manpage on Tiger/10.4:
             * ----
             * With  the way libraries used to be created, errors were possible
             * if the library was modified with ar(1) and  the  table  of
             * contents  was  not updated  by  rerunning ranlib(1).  Thus the
             * link editor, ld, warns when the modification date of a library
             * is more  recent  than  the  creation date  of its table of
             * contents.  Unfortunately, this means that you get the warning
             * even if you only copy the library.
             * ----
             *
             * This means that when we install the static archive, we need to
             * rerun ranlib afterwards.
             */
            const char *lib_args[3], *static_lib_name;
            char *tmp;
            size_t len1, len2;
            len1 = strlen(cmd_data->arglist->vals[cmd_data->arglist->num - 1]);

            static_lib_name = jlibtool_basename(cmd_data->static_name.install);
            len2 = strlen(static_lib_name);

            tmp = malloc(len1 + len2 + 2);

            snprintf(tmp, len1 + len2 + 2, "%s/%s",
                    cmd_data->arglist->vals[cmd_data->arglist->num - 1],
                    static_lib_name);

            lib_args[0] = RANLIB;
            lib_args[1] = tmp;
            lib_args[2] = NULL;
            external_spawn(cmd_data, RANLIB, lib_args);
            free(tmp);
#endif
            clear_count_chars(cctemp);
        }
        if (cmd_data->shared_name.install) {
            append_count_chars(cctemp, cmd_data->arglist);
            insert_count_chars(cctemp,
                               cmd_data->shared_name.install,
                               cctemp->num - 1);
            rv = run_command(cmd_data, cctemp);
            if (rv) {
                return rv;
            }
            clear_count_chars(cctemp);
        }
        if (cmd_data->module_name.install) {
            append_count_chars(cctemp, cmd_data->arglist);
            insert_count_chars(cctemp,
                               cmd_data->module_name.install,
                               cctemp->num - 1);
            rv = run_command(cmd_data, cctemp);
            if (rv) {
                return rv;
            }
            clear_count_chars(cctemp);
        }
        break;
    case mLink:
        if (!cmd_data->options.dry_run) {
            /* Check first to see if the dir already exists! */
            safe_mkdir(".libs");
        }

        if (cmd_data->output == otStaticLibraryOnly ||
            cmd_data->output == otLibrary) {
#ifdef RANLIB
            const char *lib_args[3];
#endif
            /* Removes compiler! */
            cmd_data->program = LIBRARIAN;
            push_count_chars(cmd_data->program_opts, LIBRARIAN_OPTS);
            push_count_chars(cmd_data->program_opts,
                             cmd_data->static_name.normal);

            rv = run_command(cmd_data, cmd_data->obj_files);
            if (rv) {
                return rv;
            }

#ifdef RANLIB
            lib_args[0] = RANLIB;
            lib_args[1] = cmd_data->static_name.normal;
            lib_args[2] = NULL;
            external_spawn(cmd_data, RANLIB, lib_args);
#endif
        }

        if (cmd_data->output == otDynamicLibraryOnly ||
            cmd_data->output == otModule ||
            cmd_data->output == otLibrary) {
            cmd_data->program = NULL;
            clear_count_chars(cmd_data->program_opts);

            append_count_chars(cmd_data->program_opts, cmd_data->arglist);
            if (cmd_data->output == otModule) {
#ifdef MODULE_OPTS
                push_count_chars(cmd_data->program_opts, MODULE_OPTS);
#endif
            } else {
#ifdef SHARED_OPTS
                push_count_chars(cmd_data->program_opts, SHARED_OPTS);
#endif
#ifdef dynamic_link_version_func
                push_count_chars(cmd_data->program_opts,
                             dynamic_link_version_func(cmd_data->version_info));
#endif
            }
            add_dynamic_link_opts(cmd_data, cmd_data->program_opts);

            rv = run_command(cmd_data, cmd_data->shared_opts.normal);
            if (rv) {
                return rv;
            }
        }
        if (cmd_data->output == otProgram) {
            rv = run_command(cmd_data, cmd_data->arglist);
            if (rv) {
                return rv;
            }
        }
        break;
    default:
        break;
    } 

    return 0;
}

void cleanup_tmp_dir(const char *dirname)
{
    DIR *dir;
    struct dirent *entry;
    char fullname[1024];

    dir = opendir(dirname);

    if (dir == NULL)
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            strcpy(fullname, dirname);
            strcat(fullname, "/");
            strcat(fullname, entry->d_name);
            remove(fullname);
        }
    }

    rmdir(dirname);
}

void cleanup_tmp_dirs(command_t *cmd_data)
{
    int d;

    for (d = 0; d < cmd_data->tmp_dirs->num; d++) {
        cleanup_tmp_dir(cmd_data->tmp_dirs->vals[d]);
    }
}

int ensure_fake_uptodate(command_t *cmd_data)
{
    /* FIXME: could do the stat/touch here, but nah... */
    const char *touch_args[3];

    if (cmd_data->mode == mInstall) {
        return 0;
    }
    if (!cmd_data->fake_output_name) {
        return 0;
    }

    touch_args[0] = "touch";
    touch_args[1] = cmd_data->fake_output_name;
    touch_args[2] = NULL;
    return external_spawn(cmd_data, "touch", touch_args);
}

/* Store the install path in the *.la file */
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