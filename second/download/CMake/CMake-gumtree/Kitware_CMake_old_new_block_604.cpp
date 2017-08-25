(useOldLinkLibs)
      {
      fprintf(fout,
              "TARGET_LINK_LIBRARIES(%s ${LINK_LIBRARIES})\n",targetName);
      }
    else
      {
      fprintf(fout, "TARGET_LINK_LIBRARIES(%s %s)\n",
              targetName,
              libsToLink.c_str());
      }