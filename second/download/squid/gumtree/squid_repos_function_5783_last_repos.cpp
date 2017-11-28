char *
get_ad_groups(char *ad_groups, krb5_context context, krb5_pac pac)
{
    krb5_error_code ret;
    RPC_UNICODE_STRING EffectiveName;
    RPC_UNICODE_STRING FullName;
    RPC_UNICODE_STRING LogonScript;
    RPC_UNICODE_STRING ProfilePath;
    RPC_UNICODE_STRING HomeDirectory;
    RPC_UNICODE_STRING HomeDirectoryDrive;
    RPC_UNICODE_STRING LogonServer;
    RPC_UNICODE_STRING LogonDomainName;
    uint32_t GroupCount=0;
    uint32_t GroupIds=0;
    uint32_t LogonDomainId=0;
    uint32_t SidCount=0;
    uint32_t ExtraSids=0;
    /*
    uint32_t ResourceGroupDomainSid=0;
    uint32_t ResourceGroupCount=0;
    uint32_t ResourceGroupIds=0;
    */
    char **Rids=NULL;
    int l=0;

    if (!ad_groups) {
        debug((char *) "%s| %s: ERR: No space to store groups\n",
              LogTime(), PROGRAM);
        return NULL;
    }

    ad_data = (krb5_data *)xcalloc(1,sizeof(krb5_data));

#define KERB_LOGON_INFO 1
    ret = krb5_pac_get_buffer(context, pac, KERB_LOGON_INFO, ad_data);
    if (check_k5_err(context, "krb5_pac_get_buffer", ret))
        goto k5clean;

    p = (unsigned char *)ad_data->data;

    debug((char *) "%s| %s: INFO: Got PAC data of lengh %d\n",
          LogTime(), PROGRAM, (int)ad_data->length);

    /* Skip 16 bytes icommon RPC header
     * Skip 4 bytes RPC unique pointer referent
     * http://msdn.microsoft.com/en-gb/library/cc237933.aspx
     */
    /* Some data are pointers to data which follows the main KRB5 LOGON structure =>
     *         So need to read the data
     * some logical consistency checks are done when analysineg the pointer data
     */
    bpos = 20;
    /* 8 bytes LogonTime
     * 8 bytes LogoffTime
     * 8 bytes KickOffTime
     * 8 bytes PasswordLastSet
     * 8 bytes PasswordCanChange
     * 8 bytes PasswordMustChange
     */
    bpos = bpos+48;
    getustr(&EffectiveName);
    getustr(&FullName);
    getustr(&LogonScript);
    getustr(&ProfilePath);
    getustr(&HomeDirectory);
    getustr(&HomeDirectoryDrive);
    /* 2 bytes LogonCount
     * 2 bytes BadPasswordCount
     * 4 bytes UserID
     * 4 bytes PrimaryGroupId
     */
    bpos = bpos+12;
    GroupCount = get4byt();
    GroupIds = get4byt();
    /* 4 bytes UserFlags
     * 16 bytes UserSessionKey
     */
    bpos = bpos+20;
    getustr(&LogonServer);
    getustr(&LogonDomainName);
    LogonDomainId = get4byt();
    /* 8 bytes Reserved1
     * 4 bytes UserAccountControl
     * 4 bytes SubAuthStatus
     * 8 bytes LastSuccessfullLogon
     * 8 bytes LastFailedLogon
     * 4 bytes FailedLogonCount
     * 4 bytes Reserved2
     */
    bpos = bpos+40;
    SidCount = get4byt();
    ExtraSids = get4byt();
    /* 4 bytes ResourceGroupDomainSid
     * 4 bytes ResourceGroupCount
     * 4 bytes ResourceGroupIds
     */
    bpos = bpos+12;
    /*
     * Read all data from structure => Now check pointers
     */
    if (checkustr(&EffectiveName)<0)
        goto k5clean;
    if (checkustr(&FullName)<0)
        goto k5clean;
    if (checkustr(&LogonScript)<0)
        goto k5clean;
    if (checkustr(&ProfilePath)<0)
        goto k5clean;
    if (checkustr(&HomeDirectory)<0)
        goto k5clean;
    if (checkustr(&HomeDirectoryDrive)<0)
        goto k5clean;
    Rids = getgids(Rids,GroupIds,GroupCount);
    if (checkustr(&LogonServer)<0)
        goto k5clean;
    if (checkustr(&LogonDomainName)<0)
        goto k5clean;
    ad_groups = getdomaingids(ad_groups,LogonDomainId,Rids,GroupCount);
    if ((ad_groups = getextrasids(ad_groups,ExtraSids,SidCount))==NULL)
        goto k5clean;

    debug((char *) "%s| %s: INFO: Read %d of %d bytes \n", LogTime(), PROGRAM, bpos, (int)ad_data->length);
    if (Rids) {
        for ( l=0; l<(int)GroupCount; l++) {
            xfree(Rids[l]);
        }
        xfree(Rids);
    }
    krb5_free_data(context, ad_data);
    return ad_groups;
k5clean:
    if (Rids) {
        for ( l=0; l<(int)GroupCount; l++) {
            xfree(Rids[l]);
        }
        xfree(Rids);
    }
    krb5_free_data(context, ad_data);
    return NULL;
}