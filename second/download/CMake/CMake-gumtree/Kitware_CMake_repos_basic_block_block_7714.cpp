{  /* append namespace separator and prefix */
          tempPool.ptr[-1] = namespaceSeparator;
          s = b->prefix->name;
          do {
            if (!poolAppendChar(&tempPool, *s))
              return XML_ERROR_NO_MEMORY;
          } while (*s++);
        }