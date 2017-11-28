char *peer_proxy_negotiate_auth(char *principal_name, char *proxy) {
    int rc = 0;
    OM_uint32 major_status, minor_status;
    gss_ctx_id_t gss_context = GSS_C_NO_CONTEXT;
    gss_name_t server_name = GSS_C_NO_NAME;
    gss_buffer_desc service = GSS_C_EMPTY_BUFFER;
    gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
    gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
    char *token = NULL;

    setbuf(stdout, NULL);
    setbuf(stdin, NULL);

    if (!proxy) {
        debugs(11, 5, HERE << "Error : No proxy server name");
        return NULL;
    }

    if (principal_name)
        debugs(11, 5,
               HERE << "Creating credential cache for " << principal_name);
    else
        debugs(11, 5, HERE << "Creating credential cache");
    rc = krb5_create_cache(NULL, principal_name);
    if (rc) {
        debugs(11, 5, HERE << "Error : Failed to create Kerberos cache");
        krb5_cleanup();
        return NULL;
    }

    service.value = (void *) xmalloc(strlen("HTTP") + strlen(proxy) + 2);
    snprintf((char *) service.value, strlen("HTTP") + strlen(proxy) + 2,
             "%s@%s", "HTTP", proxy);
    service.length = strlen((char *) service.value);

    debugs(11, 5, HERE << "Import gss name");
    major_status = gss_import_name(&minor_status, &service,
                                   gss_nt_service_name, &server_name);

    if (check_gss_err(major_status, minor_status, "gss_import_name()"))
        goto cleanup;

    debugs(11, 5, HERE << "Initialize gss security context");
    major_status = gss_init_sec_context(&minor_status,
                                        GSS_C_NO_CREDENTIAL,
                                        &gss_context,
                                        server_name,
                                        gss_mech_spnego,
                                        0,
                                        0,
                                        GSS_C_NO_CHANNEL_BINDINGS,
                                        &input_token, NULL, &output_token, NULL, NULL);

    if (check_gss_err(major_status, minor_status, "gss_init_sec_context()"))
        goto cleanup;

    debugs(11, 5, HERE << "Got token with length " << output_token.length);
    if (output_token.length) {

        token =
            (char *) base64_encode_bin((const char *) output_token.value,
                                       output_token.length);
    }

cleanup:
    gss_delete_sec_context(&minor_status, &gss_context, NULL);
    gss_release_buffer(&minor_status, &service);
    gss_release_buffer(&minor_status, &input_token);
    gss_release_buffer(&minor_status, &output_token);
    gss_release_name(&minor_status, &server_name);

    return token;
}