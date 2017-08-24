    if (useOldLinkLibs)
      {
      fprintf(fout,
              "target_link_libraries(%s ${LINK_LIBRARIES})\n",
              targetName.c_str());
      }
    else
      {
      fprintf(fout, "target_link_libraries(%s %s)\n",
              targetName.c_str(),
              libsToLink.c_str());
      }
    fclose(fout);
