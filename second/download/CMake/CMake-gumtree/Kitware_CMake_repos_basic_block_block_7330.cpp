{
  case 0:
    sec2 = '0';
    break;
  case 2:
    sec1 = fracp[-2];
    /* FALLTHROUGH */
  case 1:
    sec2 = fracp[-1];
    break;
  default:
    return (const char *) NULL;
  }