(i = 0; i < number_bidders; i++, bidder++)
    {
      if (!bidder->name || !strcmp(bidder->name, str))
        break;
    }