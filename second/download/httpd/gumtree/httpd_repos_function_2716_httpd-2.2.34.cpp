static void update_status(void)
{
    if (!quiet) {
        curr_char = (curr_char + 1) % ABTS_STAT_SIZE;
        fprintf(stdout, "\b%c", status[curr_char]);
        fflush(stdout);
    }
}