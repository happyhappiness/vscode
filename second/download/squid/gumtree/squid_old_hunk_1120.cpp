    // NP: use random port for secure outbound to IDENT_PORT
    state->conn->local.port(0);
    state->conn->remote.port(IDENT_PORT);

    // build our query from the original connection details
    state->queryMsg.init();
    state->queryMsg.Printf("%d, %d\r\n", conn->remote.port(), conn->local.port());

    ClientAdd(state, callback, data);
    hash_join(ident_hash, &state->hash);

    AsyncCall::Pointer call = commCbCall(30,3, "Ident::ConnectDone", CommConnectCbPtrFun(Ident::ConnectDone, state));
    AsyncJob::Start(new Comm::ConnOpener(state->conn, call, Ident::TheConfig.timeout));
