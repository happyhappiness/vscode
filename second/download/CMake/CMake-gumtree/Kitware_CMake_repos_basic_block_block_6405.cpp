{
    s_pSecFn->DeleteSecurityContext(nego->context);
    free(nego->context);
    nego->context = NULL;
  }