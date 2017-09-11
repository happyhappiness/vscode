      CHECK_EQ((*set_function)(set_function_handle, cbatch), 0)
          << XGBGetLastError();
      // release the elements.
      jenv->ReleaseLongArrayElements(
          joffset, reinterpret_cast<jlong *>(cbatch.offset), 0);
      jenv->DeleteLocalRef(joffset);
      if (jlabel != nullptr) {
        jenv->ReleaseFloatArrayElements(jlabel, cbatch.label, 0);
