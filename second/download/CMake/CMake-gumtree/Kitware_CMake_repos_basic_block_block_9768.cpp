(sfs.f_type) {
	case AFS_SUPER_MAGIC:
	case CIFS_SUPER_MAGIC:
	case CODA_SUPER_MAGIC:
	case NCP_SUPER_MAGIC:/* NetWare */
	case NFS_SUPER_MAGIC:
	case SMB_SUPER_MAGIC:
		t->current_filesystem->remote = 1;
		t->current_filesystem->synthetic = 0;
		break;
	case DEVFS_SUPER_MAGIC:
	case PROC_SUPER_MAGIC:
	case USBDEVICE_SUPER_MAGIC:
		t->current_filesystem->remote = 0;
		t->current_filesystem->synthetic = 1;
		break;
	default:
		t->current_filesystem->remote = 0;
		t->current_filesystem->synthetic = 0;
		break;
	}