(parser != NULL) {
      mtemp = (XML_Memory_Handling_Suite *)&(parser->m_mem);
      mtemp->malloc_fcn = malloc;
      mtemp->realloc_fcn = realloc;
      mtemp->free_fcn = free;
    }