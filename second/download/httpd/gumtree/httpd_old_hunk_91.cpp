}

/**************************************************************** 
 * 
 * Actual cgid handling... 
 */ 
static int cgid_handler(request_rec *r) 
{ 
    conn_rec *c = r->connection;
    int retval, nph, dbpos = 0; 
    char *argv0, *dbuf = NULL; 
    apr_bucket_brigade *bb;
