int 
main(int           const argc, 
     const char ** const argv ATTR_UNUSED) {

    xmlrpc_env env;
    xmlrpc_value *result;
    char *state_name;

    if (argc-1 > 0) {
        fprintf(stderr, "No arguments");
        exit(0);
    }

    /* Start up our XML-RPC client library. */
    xmlrpc_client_init(XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION);

    /* Initialize our error-handling environment. */
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

    /* Clean up our error-handling environment. */
    xmlrpc_env_clean(&env);
  
    /* Shutdown our XML-RPC client library. */
    xmlrpc_client_cleanup();

    return 0;
}