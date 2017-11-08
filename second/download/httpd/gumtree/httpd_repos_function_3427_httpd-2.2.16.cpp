int external_spawn(command_t *cmd, const char *file, const char **argv)
{
    if (!cmd->options.silent) {
        const char **argument = argv;
        printf("Executing: ");
        while (*argument) {
            printf("%s ", *argument);
            argument++;
        }
        puts("");
    }

    if (cmd->options.dry_run) {
        return 0;
    }
#if defined(__EMX__) || defined(__MINGW32__)
    return spawnvp(P_WAIT, argv[0], argv);
#else
    {
        pid_t pid;
        pid = fork();
        if (pid == 0) {
            return execvp(argv[0], (char**)argv);
        }
        else {
            int statuscode;
            waitpid(pid, &statuscode, 0);
            if (WIFEXITED(statuscode)) {
                return WEXITSTATUS(statuscode);
            }
            return 0;
        }
    }
#endif
}