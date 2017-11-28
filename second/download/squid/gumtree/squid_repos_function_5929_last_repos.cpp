int
is_dc_ok(char *domain, char *domain_controller)
{
    SMB_Handle_Type h = SMB_Connect_Server(NULL, domain_controller, domain);
    if (h == NULL)
        return 0;
    SMB_Discon(h, 0);
    return 1;
}