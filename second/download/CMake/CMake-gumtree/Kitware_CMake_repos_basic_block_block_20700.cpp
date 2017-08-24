(i >= n_required_vars) {
      cmp = 1;
    } else if (!*ptr_copy) {
      cmp = -1;
    } else {
      cmp = env_strncmp(required_vars[i].wide_eq,
                        required_vars[i].len,
                        *ptr_copy);
    }