/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#ifndef FINDINFILES_H
#define FINDINFILES_H

#include "basefilefind.h"

#include <utils/fileutils.h>

#include <QPointer>
#include <QStringListModel>

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QComboBox)

namespace TextEditor {

class TEXTEDITOR_EXPORT FindInFiles : public BaseFileFind
{
    Q_OBJECT

public:
    FindInFiles();
    ~FindInFiles();

    QString id() const;
    QString displayName() const;
    void findAll(const QString &txt, Core::FindFlags findFlags);
    QWidget *createConfigWidget();
    void writeSettings(QSettings *settings);
    void readSettings(QSettings *settings);

    void setDirectory(const Utils::FileName &directory);
    static void findOnFileSystem(const QString &path);

protected:
    Utils::FileIterator *files(const QStringList &nameFilters,
                               const QVariant &additionalParameters) const;
    QVariant additionalParameters() const;
    QString label() const;
    QString toolTip() const;

private:
    void openFileBrowser();

    Utils::FileName path() const;

    QStringListModel m_directoryStrings;
    Utils::FileName m_directorySetting;
    QPointer<QWidget> m_configWidget;
    QPointer<QComboBox> m_directory;
};

} // namespace TextEditor

#endif // FINDINFILES_H