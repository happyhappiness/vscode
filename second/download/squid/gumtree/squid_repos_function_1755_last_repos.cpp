void
storeLogRotate(void)
{
    if (NULL == storelog)
        return;

    logfileRotate(storelog, Config.Log.rotateNumber);
}