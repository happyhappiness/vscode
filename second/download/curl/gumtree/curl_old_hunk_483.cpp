          break;
        }
        break;
      }
    }

    if (!(pp->name)) { /* unknown protocol */
      /* If they have specified only this protocol, we say treat it as
         if no protocols are allowed */
      if (action == set)
        *val = 0;
      warnf(config, "unrecognized protocol '%s'\n", token);
    }
  }
  free(buffer);
  return 0;
