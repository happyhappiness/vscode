void
storeLogClose(void)
{
    if (NULL == storelog)
        return;

    logfileClose(storelog);

    storelog = NULL;
}