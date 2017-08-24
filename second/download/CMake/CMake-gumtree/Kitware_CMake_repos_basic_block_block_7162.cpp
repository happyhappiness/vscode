f(!len) {
    /* It's debatable what to return when !len. Regardless we can't return
    immediately because there may be data to decrypt (in the case we want to
    decrypt all encrypted cached data) so handle !len later in cleanup.
    */
    ; /* do nothing */
  }