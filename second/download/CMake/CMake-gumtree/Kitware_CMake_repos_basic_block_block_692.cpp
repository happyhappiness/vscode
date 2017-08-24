{
  std::string const& path = cmSystemTools::GetCMakeGUICommand();
  if (path.empty()) {
    return;
  }
  std::string const& realPath = cmSystemTools::GetRealPath(path);
  QFileInfo appPath(QString::fromLocal8Bit(realPath.c_str()));
  QDir pluginDir = appPath.dir();
  bool const foundPluginDir = pluginDir.cd("../PlugIns");
  if (foundPluginDir) {
    QApplication::addLibraryPath(pluginDir.path());
  }
}