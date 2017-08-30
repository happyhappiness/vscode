

  if (statSource.st_size != statDestination.st_size)

    {

    char msg[256];

    sprintf(msg, "CopyFile failed to copy files (sizes differ, source: %lu, dest: %lu)", statSource.st_size, statDestination.st_size);

    cmSystemTools::Error(msg);

    }

}


