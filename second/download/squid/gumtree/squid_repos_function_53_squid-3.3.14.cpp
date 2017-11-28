static char *
GSSAPI_token(const char *server)
{
    OM_uint32 major_status, minor_status;
    gss_ctx_id_t gss_context = GSS_C_NO_CONTEXT;
    gss_name_t server_name = GSS_C_NO_NAME;
    gss_buffer_desc service = GSS_C_EMPTY_BUFFER;
    gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
    gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
    char *token = NULL;

    setbuf(stdout, NULL);
    setbuf(stdin, NULL);

    if (!server) {
        fprintf(stderr, "Error: No server name\n");
        return (char *)"ERROR";
    }
    service.value = xmalloc(strlen("HTTP") + strlen(server) + 2);
    snprintf((char *) service.value, strlen("HTTP") + strlen(server) + 2, "%s@%s", "HTTP", server);
    service.length = strlen((char *) service.value);

    major_status = gss_import_name(&minor_status, &service,
                                   gss_nt_service_name, &server_name);

    if (!check_gss_err(major_status, minor_status, "gss_import_name()")) {

        major_status = gss_init_sec_context(&minor_status,
                                            GSS_C_NO_CREDENTIAL,
                                            &gss_context,
                                            server_name,
                                            gss_mech_spnego,
                                            0,
                                            0,
                                            GSS_C_NO_CHANNEL_BINDINGS,
                                            &input_token,
                                            NULL,
                                            &output_token,
                                            NULL,
                                            NULL);

        if (!check_gss_err(major_status, minor_status, "gss_init_sec_context()")) {

            if (output_token.length)
                token = (char *) base64_encode_bin((const char *) output_token.value, output_token.length);
        }
    }

    if (!output_token.length)
        token = (char *) "ERROR";
    gss_delete_sec_context(&minor_status, &gss_context, NULL);
    gss_release_buffer(&minor_status, &service);
    gss_release_buffer(&minor_status, &input_token);
    gss_release_buffer(&minor_status, &output_token);
    gss_release_name(&minor_status, &server_name);

    return token;
}