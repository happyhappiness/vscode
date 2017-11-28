void
authenticateReset(void)
{
    debugs(29, 2, "Reset authentication State.");

    // username cache is cleared via Runner registry

    /* schedule shutdown of the helpers */
    authenticateRotate();

    /* free current global config details too. */
    Auth::TheConfig.clear();
}