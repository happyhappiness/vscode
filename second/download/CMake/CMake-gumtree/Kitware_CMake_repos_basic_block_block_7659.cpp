(!tag->buf) {
            FREE(tag);
            return XML_ERROR_NO_MEMORY;
          }