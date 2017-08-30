  return this->PrivateClose(timeout);

}



/*

 * Internal dictionary mapping popen* file pointers to process handles,

 * for use when retrieving the process exit code.  See _PyPclose() below

