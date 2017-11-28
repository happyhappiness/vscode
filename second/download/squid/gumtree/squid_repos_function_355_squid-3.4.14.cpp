void
dc_disconnect()
{
    if (handle != NULL)
        SMB_Discon(handle, 0);
    handle = NULL;
}