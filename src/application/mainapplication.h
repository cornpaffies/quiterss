/* ============================================================
* QuiteRSS is a open-source cross-platform RSS/Atom news feeds reader
* Copyright (C) 2011-2021 QuiteRSS Team <quiterssteam@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
* ============================================================ */
#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#define mainApp MainApplication::getInstance()

#include <QtWidgets>
#include <qtsingleapplication.h>
#include <QNetworkDiskCache>
#include <QLocale>
#include <QLibraryInfo>
#include <QNetworkProxy>
#include <QWebEngineSettings>

#include "cookiejar.h"
#include "downloadmanager.h"
#include "mainwindow.h"
#include "ganalytics.h"

class NetworkManager;
class SplashScreen;
class UpdateFeeds;

class MainApplication : public QtSingleApplication
{
  Q_OBJECT
public:
  explicit MainApplication(int &argc, char** argv);
  ~MainApplication();

  static MainApplication *getInstance();

  bool isPortable() const;
  bool isPortableAppsCom() const;
  void setClosing();
  bool isClosing() const;
  bool isNoDebugOutput() const;
  void showClosingWidget();

  QString resourcesDir() const;
  QString dataDir() const;
  QString absolutePath(const QString &path) const;
  QString dbFileName() const;
  QString cacheDefaultDir() const;
  QString soundNotifyDefaultFile() const;
  QString styleSheetNewsDefaultFile() const;
  QString styleSheetWebDarkFile() const;

  bool storeDBMemory() const;
  bool dbFileExists() const { return dbFileExists_; }
  bool isSaveDataLastFeed() const;
  void sqlQueryExec(const QString &query);

  MainWindow *mainWindow();
  NetworkManager *networkManager();
  CookieJar *cookieJar();
  void setDiskCache();
  UpdateFeeds *updateFeeds();
  void runUserFilter(int feedId, int filterId);
  DownloadManager *downloadManager();

  void c2fLoadSettings();
  void c2fSaveSettings();
  bool c2fIsEnabled() const;
  void c2fSetEnabled(bool enabled);
  QStringList c2fGetWhitelist();
  void c2fSetWhitelist(QStringList whitelist);
  void c2fAddWhitelist(const QString &site);

  void setTranslateApplication();
  QString language() const { return langFileName_; }
  void setLanguage(const QString &lang) { langFileName_ = lang; }

  GAnalytics *analytics() const { return analytics_; }

  QNetworkProxy networkProxy() const { return networkProxy_; }
  void proxyLoadSettings();
  void proxySaveSettings(const QNetworkProxy &proxy);

public slots:
  void receiveMessage(const QString &message);
  void quitApplication();
  void reloadUserStyleBrowser();

signals:
  void signalRunUserFilter(int feedId, int filterId);
  void signalSqlQueryExec(const QString &query);

private slots:
  void commitData(QSessionManager &manager);

private:
  void createSettings();
  void createGoogleAnalytics();
  void connectDatabase();
  void loadSettings();
  void setStyleApplication();
  void showSplashScreen();
  void closeSplashScreen();
  void setProgressSplashScreen(int value);

  QUrl userStyleSheet(const QString &filePath) const;

  void setProxy();

  bool isPortableAppsCom_;
  bool isClosing_;

  bool storeDBMemory_;
  bool dbFileExists_;
  bool isSaveDataLastFeed_;
  QString styleApplication_;
  bool showSplashScreen_;
  bool updateFeedsStartUp_;

  QTranslator *translator_;
  QTranslator *qt_translator_;
  QString langFileName_;
  SplashScreen *splashScreen_;
  MainWindow *mainWindow_;
  NetworkManager *networkManager_;
  CookieJar *cookieJar_;
  QNetworkDiskCache *diskCache_;
  UpdateFeeds *updateFeeds_;
  DownloadManager *downloadManager_;
  QWidget *closingWidget_;

  QStringList c2fWhitelist_;
  bool c2fEnabled_;

  QNetworkProxy networkProxy_;
  GAnalytics *analytics_;

};

#endif // MAINAPPLICATION_H
