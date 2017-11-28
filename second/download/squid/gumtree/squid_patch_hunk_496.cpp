                 major_status = gss_import_name(&minor_status, &service,
                                                (gss_OID) GSS_C_NULL_OID, &server_name);
 
             } else {
                 server_name = GSS_C_NO_NAME;
                 major_status = GSS_S_COMPLETE;
+                minor_status = 0;
             }
         } else {
             major_status = gss_import_name(&minor_status, &service,
                                            gss_nt_service_name, &server_name);
         }
 
-        if (check_gss_err(major_status, minor_status, "gss_import_name()", log))
+        if (check_gss_err(major_status, minor_status, "gss_import_name()", log, 1))
             goto cleanup;
 
         major_status =
             gss_acquire_cred(&minor_status, server_name, GSS_C_INDEFINITE,
                              GSS_C_NO_OID_SET, GSS_C_ACCEPT, &server_creds, NULL, NULL);
-        if (check_gss_err(major_status, minor_status, "gss_acquire_cred()", log))
+        if (check_gss_err(major_status, minor_status, "gss_acquire_cred()", log, 1))
             goto cleanup;
 
         major_status = gss_accept_sec_context(&minor_status,
                                               &gss_context,
                                               server_creds,
                                               &input_token,
                                               GSS_C_NO_CHANNEL_BINDINGS,
                                               &client_name, NULL, &output_token, &ret_flags, NULL, NULL);
 
         if (output_token.length) {
             spnegoToken = (const unsigned char *) output_token.value;
             spnegoTokenLength = output_token.length;
-            token = (char *) xmalloc(base64_encode_len(spnegoTokenLength));
+            token = (char *) xmalloc((size_t)base64_encode_len((int)spnegoTokenLength));
             if (token == NULL) {
                 debug((char *) "%s| %s: ERROR: Not enough memory\n", LogTime(), PROGRAM);
                 fprintf(stdout, "BH Not enough memory\n");
                 goto cleanup;
             }
-            base64_encode_str(token, base64_encode_len(spnegoTokenLength),
-                              (const char *) spnegoToken, spnegoTokenLength);
+            base64_encode_str(token, base64_encode_len((int)spnegoTokenLength),
+                              (const char *) spnegoToken, (int)spnegoTokenLength);
 
-            if (check_gss_err(major_status, minor_status, "gss_accept_sec_context()", log))
+            if (check_gss_err(major_status, minor_status, "gss_accept_sec_context()", log, 1))
                 goto cleanup;
             if (major_status & GSS_S_CONTINUE_NEEDED) {
                 debug((char *) "%s| %s: INFO: continuation needed\n", LogTime(), PROGRAM);
                 fprintf(stdout, "TT %s\n", token);
                 goto cleanup;
             }
             gss_release_buffer(&minor_status, &output_token);
             major_status =
                 gss_display_name(&minor_status, client_name, &output_token,
                                  NULL);
 
-            if (check_gss_err(major_status, minor_status, "gss_display_name()", log))
+            if (check_gss_err(major_status, minor_status, "gss_display_name()", log, 1))
                 goto cleanup;
             user = (char *) xmalloc(output_token.length + 1);
             if (user == NULL) {
                 debug((char *) "%s| %s: ERROR: Not enough memory\n", LogTime(), PROGRAM);
                 fprintf(stdout, "BH Not enough memory\n");
                 goto cleanup;
             }
             memcpy(user, output_token.value, output_token.length);
             user[output_token.length] = '\0';
             if (norealm && (p = strchr(user, '@')) != NULL) {
                 *p = '\0';
             }
+
+#if HAVE_PAC_SUPPORT
+            ret = krb5_init_context(&context);
+            if (!check_k5_err(context, "krb5_init_context", ret)) {
+#if HAVE_HEIMDAL_KERBEROS
+#define ADWIN2KPAC 128
+                major_status = gsskrb5_extract_authz_data_from_sec_context(&minor_status,
+                               gss_context, ADWIN2KPAC, &data_set);
+                if (!check_gss_err(major_status, minor_status,
+                                   "gsskrb5_extract_authz_data_from_sec_context()", log, 0)) {
+                    ret = krb5_pac_parse(context, data_set.value, data_set.length, &pac);
+                    gss_release_buffer(&minor_status, &data_set);
+                    if (!check_k5_err(context, "krb5_pac_parse", ret)) {
+                        ag = get_ad_groups((char *)&ad_groups, context, pac);
+                        krb5_pac_free(context, pac);
+                    }
+                    krb5_free_context(context);
+                }
+#else
+                type_id.value = (void *)"mspac";
+                type_id.length = strlen((char *)type_id.value);
+#define KRB5PACLOGONINFO        1
+                major_status = gss_map_name_to_any(&minor_status, client_name, KRB5PACLOGONINFO, &type_id, (gss_any_t *)&pac);
+                if (!check_gss_err(major_status, minor_status, "gss_map_name_to_any()", log, 0)) {
+                    ag = get_ad_groups((char *)&ad_groups,context, pac);
+                }
+                (void)gss_release_any_name_mapping(&minor_status, client_name, &type_id, (gss_any_t *)&pac);
+                krb5_free_context(context);
+#endif
+            }
+            if (ag) {
+                debug((char *) "%s| %s: DEBUG: Groups %s\n", LogTime(), PROGRAM, ag);
+            }
+#endif
             fprintf(stdout, "AF %s %s\n", token, user);
-            debug((char *) "%s| %s: DEBUG: AF %s %s\n", LogTime(), PROGRAM, token, rfc1738_escape(user));
+            rfc_user = rfc1738_escape(user);
+            debug((char *) "%s| %s: DEBUG: AF %s %s\n", LogTime(), PROGRAM, token, rfc_user);
             if (log)
                 fprintf(stderr, "%s| %s: INFO: User %s authenticated\n", LogTime(),
                         PROGRAM, rfc1738_escape(user));
             goto cleanup;
         } else {
-            if (check_gss_err(major_status, minor_status, "gss_accept_sec_context()", log))
+            if (check_gss_err(major_status, minor_status, "gss_accept_sec_context()", log, 1))
                 goto cleanup;
             if (major_status & GSS_S_CONTINUE_NEEDED) {
                 debug((char *) "%s| %s: INFO: continuation needed\n", LogTime(), PROGRAM);
                 fprintf(stdout, "NA %s\n", token);
                 goto cleanup;
             }
             gss_release_buffer(&minor_status, &output_token);
             major_status =
                 gss_display_name(&minor_status, client_name, &output_token,
                                  NULL);
 
-            if (check_gss_err(major_status, minor_status, "gss_display_name()", log))
+            if (check_gss_err(major_status, minor_status, "gss_display_name()", log, 1))
                 goto cleanup;
             /*
              *  Return dummy token AA. May need an extra return tag then AF
              */
             user = (char *) xmalloc(output_token.length + 1);
             if (user == NULL) {
