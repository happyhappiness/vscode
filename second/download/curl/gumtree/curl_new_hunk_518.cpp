          /* don't abort operation, just issue a warning */
          SET_SOCKERRNO(0);
          warnf(clientp, "Could not set TCP_KEEPINTVL!\n");
          return 0;
        }
#endif
#if !defined(TCP_KEEPIDLE) || !defined(TCP_KEEPINTVL)
        warnf(clientp, "Keep-alive functionality somewhat crippled due to "
              "missing support in your operating system!\n");
#endif
      }
    }
    break;
  default:
    break;
  }
