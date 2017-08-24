{
      /* We opened a reparse point but it was not a symlink. Try again. */
      fs__stat_impl(req, 0);

    }