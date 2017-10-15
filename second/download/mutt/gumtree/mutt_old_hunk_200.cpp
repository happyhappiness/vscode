       * multipart/encrypted, cache signature verification
       * status.
       */
      if (mutt_is_multipart_signed (tattach) && !tattach->next)
        a->goodsig |= tattach->goodsig;
    
      if (s->flags & M_DISPLAY)
        {
          state_puts ("\n", s);
          state_attach_puts (is_signed?
             _("[-- End of PGP/MIME signed and encrypted data --]\n"):
             _("[-- End of PGP/MIME encrypted data --]\n"),
                             s);
