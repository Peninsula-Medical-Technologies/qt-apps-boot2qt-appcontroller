/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of QtEnterprise Embedded.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include <QObject>
#include <QProcess>
#include <QMap>

class QSocketNotifier;

struct Config {
    enum Flag {
        PrintDebugMessages = 0x01
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    enum DebugInterface{
        LocalDebugInterface,
        PublicDebugInterface
    };

    Config() : flags(0) { }

    QString base;
    QString platform;
    QMap<QString,QString> env;
    QStringList args;
    Flags flags;
    DebugInterface debugInterface;
};

class Process : public QObject
{
    Q_OBJECT
public:
    Process();
    virtual ~Process();
    void start(const QStringList &args);
    void setSocketNotifier(QSocketNotifier*);
    void setDebug();
    void setConfig(const Config &);
public slots:
    void stop();
private slots:
    void readyReadStandardError();
    void readyReadStandardOutput();
    void finished(int, QProcess::ExitStatus);
    void error(QProcess::ProcessError);
    void incomingConnection(int);
private:
    void startup(QStringList);
    QProcess *mProcess;
    int mDebuggee;
    bool mDebug;
    Config mConfig;
    QString mBinary;
};
