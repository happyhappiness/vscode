void
redirectShutdown(void)
{
    if (!redirectors)
        return;

    helperShutdown(redirectors);

    if (!shutting_down)
        return;

    helperFree(redirectors);

    redirectors = NULL;
}