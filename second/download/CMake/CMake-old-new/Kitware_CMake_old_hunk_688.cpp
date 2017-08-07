    if (useOldLinkLibs)
      {
      fprintf(fout,
              "target_link_libraries(%s ${LINK_LIBRARIES})\n",targetName);
      }
    else
      {
      fprintf(fout, "target_link_libraries(%s %s)\n",
              targetName,
              libsToLink.c_str());
      }
    fclose(fout);
