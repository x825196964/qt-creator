/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#ifndef PROITEMS_H
#define PROITEMS_H

#include <QtCore/QString>
#include <QtCore/QList>

QT_BEGIN_NAMESPACE

class ProItem
{
public:
    enum ProItemKind {
        FunctionKind,
        ConditionKind,
        OperatorKind,
        VariableKind,
        BlockKind
    };

    enum ProItemReturn {
        ReturnFalse,
        ReturnTrue,
        ReturnBreak,
        ReturnNext,
        ReturnLoop,
        ReturnSkip,
        ReturnReturn
   };

    ProItem() : m_lineNumber(0) {}
    virtual ~ProItem() {}

    virtual ProItemKind kind() const = 0;

    int lineNumber() const { return m_lineNumber; }
    void setLineNumber(int lineNumber) { m_lineNumber = lineNumber; }

private:
    int m_lineNumber;
};

class ProBlock : public ProItem
{
public:
    enum ProBlockKind {
        NormalKind          = 0x00,
        ScopeKind           = 0x01,
        ScopeContentsKind   = 0x02,
        ProFileKind         = 0x08,
        FunctionBodyKind    = 0x10,
        SingleLine          = 0x80
    };

    ProBlock();
    ~ProBlock();

    void appendItem(ProItem *proitem) { m_proitems << proitem; }
    QList<ProItem *> items() const { return m_proitems; }
    void setBlockKind(int blockKind) { m_blockKind = blockKind; }
    int blockKind() const { return m_blockKind; }

    void ref() { ++m_refCount; }
    void deref() { if (!--m_refCount) delete this; }

    ProItem::ProItemKind kind() const;

private:
    QList<ProItem *> m_proitems;
    int m_blockKind;
    int m_refCount;
};

class ProVariable : public ProItem
{
public:
    enum VariableOperator {
        AddOperator         = 0,
        RemoveOperator      = 1,
        ReplaceOperator     = 2,
        SetOperator         = 3,
        UniqueAddOperator   = 4
    };

    ProVariable(const QString &name) : m_variableKind(SetOperator), m_variable(name) {}
    void setVariableOperator(VariableOperator variableKind) { m_variableKind = variableKind; }
    VariableOperator variableOperator() const { return m_variableKind; }
    void setVariable(const QString &name) { m_variable = name; }
    QString variable() const { return m_variable; }
    void setValue(const QString &value) { m_value = value; }
    QString value() const { return m_value; }

    ProItem::ProItemKind kind() const;

private:
    VariableOperator m_variableKind;
    QString m_variable;
    QString m_value;
};

class ProFunction : public ProItem
{
public:
    explicit ProFunction(const QString &text) : m_text(text) {}
    void setText(const QString &text) { m_text = text; }
    QString text() const { return m_text; }

    ProItem::ProItemKind kind() const;

private:
    QString m_text;
};

class ProCondition : public ProItem
{
public:
    explicit ProCondition(const QString &text) : m_text(text) {}
    void setText(const QString &text) { m_text = text; }
    QString text() const { return m_text; }

    ProItem::ProItemKind kind() const;

private:
    QString m_text;
};

class ProOperator : public ProItem
{
public:
    enum OperatorKind {
        OrOperator      = 1,
        NotOperator     = 2
    };

    explicit ProOperator(OperatorKind operatorKind) : m_operatorKind(operatorKind) {}
    void setOperatorKind(OperatorKind operatorKind) { m_operatorKind = operatorKind; }
    OperatorKind operatorKind() const { return m_operatorKind; }

    ProItem::ProItemKind kind() const;

private:
    OperatorKind m_operatorKind;
};

class ProFile : public ProBlock
{
public:
    explicit ProFile(const QString &fileName);

    QString displayFileName() const { return m_displayFileName; }
    QString fileName() const { return m_fileName; }
    QString directoryName() const { return m_directoryName; }

private:
    QString m_fileName;
    QString m_displayFileName;
    QString m_directoryName;
};

QT_END_NAMESPACE

#endif // PROITEMS_H
