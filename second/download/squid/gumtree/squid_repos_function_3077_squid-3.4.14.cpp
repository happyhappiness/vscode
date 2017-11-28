void
StoreEntry::flush()
{
    if (EBIT_TEST(flags, DELAY_SENDING)) {
        EBIT_CLR(flags, DELAY_SENDING);
        invokeHandlers();
    }
}