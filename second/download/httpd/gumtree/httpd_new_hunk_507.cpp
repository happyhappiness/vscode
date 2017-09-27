            break;
        }
    }
}

/*
 *  Access Handler
 */
int ssl_hook_Access(request_rec *r)
{
    SSLDirConfigRec *dc = myDirConfig(r);
    SSLSrvConfigRec *sc = mySrvConfig(r->server);
