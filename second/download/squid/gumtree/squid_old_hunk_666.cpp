                    PROGRAM);
        return (1);
    }
    return (0);
}

int
main(int argc, char *const argv[])
{
    char buf[MAX_AUTHTOKEN_LEN];
    char *c, *p;
    char *user = NULL;
    char *rfc_user = NULL;
#if HAVE_PAC_SUPPORT
    char ad_groups[MAX_PAC_GROUP_SIZE];
    char *ag=NULL;
    krb5_context context = NULL;
    krb5_error_code ret;
    krb5_pac pac;
#if HAVE_HEIMDAL_KERBEROS
    gss_buffer_desc data_set = GSS_C_EMPTY_BUFFER;
#else
    gss_buffer_desc type_id = GSS_C_EMPTY_BUFFER;
#endif
#endif
    long length = 0;
    static int err = 0;
    int opt, log = 0, norealm = 0;
    OM_uint32 ret_flags = 0, spnego_flag = 0;
    char *service_name = (char *) "HTTP", *host_name = NULL;
    char *token = NULL;
    char *service_principal = NULL;
    OM_uint32 major_status, minor_status;
    gss_ctx_id_t gss_context = GSS_C_NO_CONTEXT;
    gss_name_t client_name = GSS_C_NO_NAME;
    gss_name_t server_name = GSS_C_NO_NAME;
    gss_cred_id_t server_creds = GSS_C_NO_CREDENTIAL;
    gss_buffer_desc service = GSS_C_EMPTY_BUFFER;
