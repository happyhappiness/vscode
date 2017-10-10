			 * NEEDSWORK: shouldn't this be flagged
			 * as an error???
			 */
			free_fragment_list(patch->fragments);
			patch->fragments = NULL;
		} else if (status) {
			return error(_("failed to read %s"), patch->old_name);
		}
	}

	img = strbuf_detach(&buf, &len);
	prepare_image(image, img, len, !patch->is_binary);
	return 0;
