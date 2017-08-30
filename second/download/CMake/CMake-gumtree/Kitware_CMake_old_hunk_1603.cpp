    xmlrpc_env_init(&env);



    /* Call the famous server at UserLand. */

    result = xmlrpc_client_call(&env, "http://betty.userland.com/RPC2",

        "examples.getStateName",

        "(i)", (xmlrpc_int32) 41);

    die_if_fault_occurred(&env);

    

    /* Get our state name and print it out. */

    xmlrpc_parse_value(&env, result, "s", &state_name);

    die_if_fault_occurred(&env);

    printf("%s\n", state_name);

    

    /* Dispose of our result value. */

    xmlrpc_DECREF(result);
