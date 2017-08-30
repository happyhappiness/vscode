  if(statSource.st_size != finSource.gcount() ||

     statSource.st_size != finDestination.gcount())

    {

    char msg[256];

    sprintf(msg, "FilesDiffer failed to read files (allocated: %lu, source: %lu, dest: %lu)", statSource.st_size, finSource.gcount(), finDestination.gcount());

    cmSystemTools::Error(msg);

    delete [] source_buf;

    delete [] dest_buf;

    return false;

    }



  finSource.close();

  finDestination.close();



  int ret = memcmp((const void*)source_buf, 

                   (const void*)dest_buf, 

                   statSource.st_size);

