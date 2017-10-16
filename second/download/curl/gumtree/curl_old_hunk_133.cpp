    multi = multi_start;
    multi_start = multi_start->next;
    free (multi);
  }
}

/***************************************************************************
 *
 * formparse()
 *
 * Reads a 'name=value' paramter and builds the appropriate linked list.
 *
