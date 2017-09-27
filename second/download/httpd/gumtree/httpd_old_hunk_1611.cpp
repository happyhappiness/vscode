    }

    /* create the ldap session handle
    */
    if (NULL == ldc->ldap)
    {
       rc = uldap_connection_init( r, ldc );
       if (LDAP_SUCCESS != rc)
       {
           return rc;
       }
    }


    /* loop trying to bind up to 10 times if LDAP_SERVER_DOWN error is
     * returned.  Break out of the loop on Success or any other error.
     *
     * NOTE: Looping is probably not a great idea. If the server isn't
     * responding the chances it will respond after a few tries are poor.
     * However, the original code looped and it only happens on
     * the error condition.
      */
    for (failures=0; failures<10; failures++)
    {
        rc = ldap_simple_bind_s(ldc->ldap,
                                (char *)ldc->binddn,
                                (char *)ldc->bindpw);
        if (!AP_LDAP_IS_SERVER_DOWN(rc)) {
            break;
        } else if (failures == 5) {
           /* attempt to init the connection once again */
           uldap_connection_unbind( ldc );
           rc = uldap_connection_init( r, ldc );
           if (LDAP_SUCCESS != rc)
           {
               break;
           }
       }
    }

    /* free the handle if there was an error
    */
    if (LDAP_SUCCESS != rc)
    {
       uldap_connection_unbind(ldc);
        ldc->reason = "LDAP: ldap_simple_bind_s() failed";
    }
    else {
        ldc->bound = 1;
        ldc->reason = "LDAP: connection open successful";
    }

