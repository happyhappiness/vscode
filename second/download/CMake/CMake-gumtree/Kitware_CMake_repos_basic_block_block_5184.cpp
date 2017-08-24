{
  case PROT_CLEAR:
    return 'C';
  case PROT_SAFE:
    return 'S';
  case PROT_CONFIDENTIAL:
    return 'E';
  case PROT_PRIVATE:
    return 'P';
  case PROT_CMD:
    /* Fall through */
  default:
    /* Those 2 cases should not be reached! */
    break;
  }