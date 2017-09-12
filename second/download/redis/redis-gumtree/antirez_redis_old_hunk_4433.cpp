      addReply(c,shared.ok);
    } else {
      c->authenticated = 0;
      addReply(c,shared.err);
    }
}

