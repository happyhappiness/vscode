          /* don't abort operation, just issue a warning */
          SET_SOCKERRNO(0);
          warnf(clientp, "Could not set TCP_KEEPINTVL!\n");
          return 0;
        }
#endif
      }
    }
    break;
  default:
    break;
  }
