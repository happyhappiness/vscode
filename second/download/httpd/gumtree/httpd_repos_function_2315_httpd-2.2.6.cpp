static void mpm_term(void)
{
    RemoveConsoleHandler();
    wait_to_finish = 0;
    NXThreadYield();
}