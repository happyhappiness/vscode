    fprintf(stderr,"*** Failed LOADED COMMAND Final Pass\n");
    }
}

static void Destructor(void *inf) 
{
  cmLoadedCommandInfo *info = (cmLoadedCommandInfo *)inf;
  /* get our client data from initial pass */
