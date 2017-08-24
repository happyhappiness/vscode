{
#ifdef HAVE_MF_HC3
	case LZMA_MF_HC3:
		mf->find = &lzma_mf_hc3_find;
		mf->skip = &lzma_mf_hc3_skip;
		break;
#endif
#ifdef HAVE_MF_HC4
	case LZMA_MF_HC4:
		mf->find = &lzma_mf_hc4_find;
		mf->skip = &lzma_mf_hc4_skip;
		break;
#endif
#ifdef HAVE_MF_BT2
	case LZMA_MF_BT2:
		mf->find = &lzma_mf_bt2_find;
		mf->skip = &lzma_mf_bt2_skip;
		break;
#endif
#ifdef HAVE_MF_BT3
	case LZMA_MF_BT3:
		mf->find = &lzma_mf_bt3_find;
		mf->skip = &lzma_mf_bt3_skip;
		break;
#endif
#ifdef HAVE_MF_BT4
	case LZMA_MF_BT4:
		mf->find = &lzma_mf_bt4_find;
		mf->skip = &lzma_mf_bt4_skip;
		break;
#endif

	default:
		return true;
	}