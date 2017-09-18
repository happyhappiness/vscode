    exit(1);
}

static void interrupted(void)
{
    fprintf(stderr, "Interrupted.\n");
    cleanup_tempfile_and_exit(1);
}

static void terminate(void)
{
#ifdef NETWARE
    pressanykey();
