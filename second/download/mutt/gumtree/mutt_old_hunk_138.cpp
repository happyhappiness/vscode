     * multipart/encrypted, cache signature verification
     * status.
     *
     */
    
    if (mutt_is_multipart_signed (tattach) && !tattach->next)
      p->goodsig |= tattach->goodsig;
    
    if (s->flags & M_DISPLAY)
    {
      state_puts ("\n", s);
      state_attach_puts (_("[-- End of PGP/MIME encrypted data --]\n"), s);
    }
