const char *who_am_i(void)
{
    return am_sender ? "sender" : am_generator ? "generator" : "receiver";
}