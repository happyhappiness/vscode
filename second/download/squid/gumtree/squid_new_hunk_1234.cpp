    if (http->getConn() != NULL && http->getConn()->getAuth() != NULL)
        proxy_auth_msg = http->getConn()->getAuth()->denyMessage("<null>");
    else if (http->request->auth_user_request != NULL)
        proxy_auth_msg = http->request->auth_user_request->denyMessage("<null>");
#endif

    if (!answer.allowed()) {
        // auth has a grace period where credentials can be expired but okay not to challenge.

        /* Send an auth challenge or error */
        // XXX: do we still need aclIsProxyAuth() ?
        bool auth_challenge = (answer == ACCESS_AUTH_REQUIRED || aclIsProxyAuth(AclMatchedName));
        debugs(85, 5, "Access Denied: " << http->uri);
