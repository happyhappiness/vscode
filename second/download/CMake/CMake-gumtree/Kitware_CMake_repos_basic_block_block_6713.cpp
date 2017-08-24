{
        case 0:
          /* This is the expected response. There was no data but only
             the close notify alert */
          done = 1;
          break;
        case GNUTLS_E_AGAIN:
        case GNUTLS_E_INTERRUPTED:
          infof(data, "GNUTLS_E_AGAIN || GNUTLS_E_INTERRUPTED\n");
          break;
        default:
          retval = -1;
          done = 1;
          break;
        }