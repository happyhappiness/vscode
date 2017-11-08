static int update_window(void *ctx, void *val)
{
    input_consumed_signal(ctx, val);
    return 1;
}