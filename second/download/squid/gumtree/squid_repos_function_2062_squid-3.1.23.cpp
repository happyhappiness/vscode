void
storeLogRotate(void)
{
    if (NULL == storelog)
        return;

    logfileRotate(storelog);
}