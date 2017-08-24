(i = 0; i < number_bidders; i++, bidder++)
  {
    /* Program bidder name set to filter name after initialization */
    if (bidder->data && !bidder->name)
      break;
  }