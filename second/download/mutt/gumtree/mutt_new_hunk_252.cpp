	if ((flags & CH_UPDATE_REFS) &&
	    ascii_strncasecmp ("References:", buf, 11) == 0)
	  continue;
	if ((flags & CH_UPDATE_IRT) &&
	    ascii_strncasecmp ("In-Reply-To:", buf, 12) == 0)
	  continue;
        if (flags & CH_UPDATE_LABEL &&
            ascii_strncasecmp ("X-Label:", buf, 8) == 0)
          continue;

	ignore = 0;
      }

      if (!ignore && fputs (buf, out) == EOF)
	return (-1);
    }
