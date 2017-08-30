{
      fprintf(fout, "TARGET_LINK_LIBRARIES(%s %s)\n",
              targetName,
              libsToLink.c_str());
      }