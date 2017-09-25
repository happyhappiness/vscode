    env = ap_create_environment(r->pool, r->subprocess_env); 

    if ((retval = connect_to_daemon(&sd, r, conf)) != OK) {
        return retval;
    }

    send_req(sd, r, argv0, env, CGI_REQ); 

    /* We are putting the socket discriptor into an apr_file_t so that we can
     * use a pipe bucket to send the data to the client.
     * Note that this does not register a cleanup for the socket.  We did
     * that explicitly right after we created the socket.
     */
    apr_os_file_put(&tempsock, &sd, 0, r->pool);

    if ((argv0 = strrchr(r->filename, '/')) != NULL) 
        argv0++; 
    else 
        argv0 = r->filename; 

