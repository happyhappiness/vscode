    server.repl_transfer_s = -1;
    server.repl_state = REPL_STATE_CONNECT;
    return;
}

int connectWithMaster(void) {
