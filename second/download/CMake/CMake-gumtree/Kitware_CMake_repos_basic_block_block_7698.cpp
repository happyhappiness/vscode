(p = tagStack; p; p = p->parent)
      if (p->name.str == binding->uri)
        p->name.str = uri