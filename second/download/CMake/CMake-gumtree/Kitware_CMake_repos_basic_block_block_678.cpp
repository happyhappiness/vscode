{
        dialog.setSourceDirectory(QString::fromLocal8Bit(filePath.c_str()));
        dialog.setBinaryDirectory(QString::fromLocal8Bit(
          cmSystemTools::CollapseFullPath(".").c_str()));
      }