            fprintf(stderr,"Error: %s\n",c->context->errstr);
            exit(1);
        }
        if (reply != NULL)
            clientDone(c);
    }
}

