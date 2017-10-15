      /* 
       * if a multipart/signed is the _only_ sub-part of a
       * multipart/encrypted, cache signature verification
       * status.
       */
      if (mutt_is_multipart_signed (tattach) && !tattach->next)
        orig_body->goodsig |= tattach->goodsig;
    
      if (s->flags & M_DISPLAY)
        {
          state_puts ("\n", s);
          state_attach_puts (is_signed?
             _("[-- End of PGP/MIME signed and encrypted data --]\n"):
