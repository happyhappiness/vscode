void
redirectShutdown(void)
{
    if (!redirectors)
        return;

    helperShutdown(redirectors);

    if (!shutting_down)
        return;

    delete redirectors;
    redirectors = NULL;
}