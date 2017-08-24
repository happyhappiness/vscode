{
          char *temp = (char *)REALLOC(groupConnector, groupSize *= 2);
          if (temp == NULL)
            return XML_ERROR_NO_MEMORY;
          groupConnector = temp;
          if (dtd->scaffIndex) {
            int *temp = (int *)REALLOC(dtd->scaffIndex,
                          groupSize * sizeof(int));
            if (temp == NULL)
              return XML_ERROR_NO_MEMORY;
            dtd->scaffIndex = temp;
          }
        }