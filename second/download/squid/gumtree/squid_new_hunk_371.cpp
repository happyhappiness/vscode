    char *token = NULL;
    char *tmp_line = NULL;
    int tmp_line_len = 0;
    int err_count = 0;
    int is_pipe = 0;

    debugs(3, DBG_IMPORTANT, "Processing Configuration File: " << file_name << " (depth " << depth << ")");
    if (depth > 16) {
        fatalf("WARNING: can't include %s: includes are nested too deeply (>16)!\n", file_name);
        return 1;
    }

    if (file_name[0] == '!' || file_name[0] == '|') {
