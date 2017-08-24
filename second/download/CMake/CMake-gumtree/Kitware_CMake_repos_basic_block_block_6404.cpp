{
    s_pSecFn->FreeCredentialsHandle(nego->credentials);
    free(nego->credentials);
    nego->credentials = NULL;
  }