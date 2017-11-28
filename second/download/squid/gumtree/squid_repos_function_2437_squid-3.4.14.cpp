void
redirectShutdown(void)
{
    /** FIXME: Temporary unified helpers Shutdown
     * When and if needed for more helpers a separated shutdown
     * method will be added for each of them.
     */
    if (!storeIds && !redirectors)
        return;

    if (redirectors)
        helperShutdown(redirectors);

    if (storeIds)
        helperShutdown(storeIds);

    if (!shutting_down)
        return;

    delete redirectors;
    redirectors = NULL;

    delete storeIds;
    storeIds = NULL;

}