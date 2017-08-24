{
	default:
	case OPT_BOOT_TYPE_AUTO:
		/* Try detecting a media type of the boot image. */
		entry = iso9660->el_torito.boot->file->entry;
		if (archive_entry_size(entry) == FD_1_2M_SIZE)
			iso9660->el_torito.media_type =
			    BOOT_MEDIA_1_2M_DISKETTE;
		else if (archive_entry_size(entry) == FD_1_44M_SIZE)
			iso9660->el_torito.media_type =
			    BOOT_MEDIA_1_44M_DISKETTE;
		else if (archive_entry_size(entry) == FD_2_88M_SIZE)
			iso9660->el_torito.media_type =
			    BOOT_MEDIA_2_88M_DISKETTE;
		else
			/* We cannot decide whether the boot image is
			 * hard-disk. */
			iso9660->el_torito.media_type =
			    BOOT_MEDIA_NO_EMULATION;
		break;
	case OPT_BOOT_TYPE_NO_EMU:
		iso9660->el_torito.media_type = BOOT_MEDIA_NO_EMULATION;
		break;
	case OPT_BOOT_TYPE_HARD_DISK:
		iso9660->el_torito.media_type = BOOT_MEDIA_HARD_DISK;
		break;
	case OPT_BOOT_TYPE_FD:
		entry = iso9660->el_torito.boot->file->entry;
		if (archive_entry_size(entry) <= FD_1_2M_SIZE)
			iso9660->el_torito.media_type =
			    BOOT_MEDIA_1_2M_DISKETTE;
		else if (archive_entry_size(entry) <= FD_1_44M_SIZE)
			iso9660->el_torito.media_type =
			    BOOT_MEDIA_1_44M_DISKETTE;
		else if (archive_entry_size(entry) <= FD_2_88M_SIZE)
			iso9660->el_torito.media_type =
			    BOOT_MEDIA_2_88M_DISKETTE;
		else {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Boot image file(``%s'') size is too big "
			    "for fd type.",
			    iso9660->el_torito.boot_filename.s);
			return (ARCHIVE_FATAL);
		}
		break;
	}