    ldb.active = 0;
}

/* Wrapper for EVAL / EVALSHA that enables debugging, and makes sure
 * that when EVAL returns, whatever happened, the session is ended. */
void evalGenericCommandWithDebugging(client *c, int evalsha) {
