             if (argused == 0 && a + 1 < argc) {
                 if (arg[1] == 'o' && !arg[2]) {
                     arg = argv[++a];
                     argused = parse_output_file_name(arg, cmd_data);
                 } else if (strcmp(arg+1, "MT") == 0) {
                     if (!cmd_data->options.silent) {
-                        printf("Adding: %s", arg);
+                        printf("Adding: %s\n", arg);
                     }
                     push_count_chars(cmd_data->arglist, arg);
                     arg = argv[++a];
                     if (!cmd_data->options.silent) {
                         printf(" %s\n", arg);
                     }
