                        ap_rputs("Dying", r);
                        break;
                    default:
                        ap_rputs("?STATE?", r);
                        break;
                    }
                    
                    ap_rprintf(r, "] "
#ifdef HAVE_TIMES
                               "u%g s%g cu%g cs%g"
#endif
                               "\n %ld %ld (",
#ifdef HAVE_TIMES
