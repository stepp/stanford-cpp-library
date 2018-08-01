/*
 * File: qgradiobutton.cpp
 * -----------------------
 *
 * @version 2018/06/25
 * - initial version
 */

#ifdef SPL_QT_GUI
#include "qgradiobutton.h"
#include "qgwindow.h"
#include "strlib.h"

_Internal_QRadioButton::_Internal_QRadioButton(QGRadioButton* qgradioButton, bool checked, QWidget* parent)
        : QRadioButton(parent),
          _qgradioButton(qgradioButton) {
    setChecked(checked);
    // We handle the clicked signal rather than toggled because, in a radio button group,
    // the toggled signal will fire twice: once for the radio button clicked, and once
    // for the other button that was unchecked.
    connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
}

void _Internal_QRadioButton::handleClick() {
    QGEvent changeEvent(
                /* class  */ QGEvent::CHANGE_EVENT,
                /* type   */ QGEvent::STATE_CHANGED,
                /* name   */ "change",
                /* source */ _qgradioButton);
    changeEvent.setActionCommand(_qgradioButton->getActionCommand());
    _qgradioButton->fireEvent(changeEvent);
}

QSize _Internal_QRadioButton::sizeHint() const {
    if (hasPreferredSize()) {
        return getPreferredSize();
    } else {
        return QRadioButton::sizeHint();
    }
}


Map<std::string, QButtonGroup*> QGRadioButton::_buttonGroups;

QGRadioButton::QGRadioButton(const std::string& text, const std::string& group, bool checked, QWidget* parent) {
    _iqradioButton = new _Internal_QRadioButton(this, checked, getInternalParent(parent));
    QButtonGroup* buttonGroup = getButtonGroup(group);
    buttonGroup->addButton(_iqradioButton);
    setText(text);
}

QGRadioButton::~QGRadioButton() {
    // TODO: delete _iqradioButton;
    _iqradioButton = nullptr;
}

std::string QGRadioButton::getActionCommand() const {
    if (_actionCommand.empty()) {
        return getText();
    } else {
        return _actionCommand;
    }
}

_Internal_QWidget* QGRadioButton::getInternalWidget() const {
    return _iqradioButton;
}

std::string QGRadioButton::getText() const {
    return _iqradioButton->text().toStdString();
}

std::string QGRadioButton::getType() const {
    return "QGRadioButton";
}

QWidget* QGRadioButton::getWidget() const {
    return static_cast<QWidget*>(_iqradioButton);
}

bool QGRadioButton::isChecked() const {
    return _iqradioButton->isChecked();
}

bool QGRadioButton::isSelected() const {
    return _iqradioButton->isChecked();
}

void QGRadioButton::removeActionListener() {
    removeEventListener("change");
}

void QGRadioButton::setActionListener(QGEventListener func) {
    setEventListener("change", func);
}

void QGRadioButton::setActionListener(QGEventListenerVoid func) {
    setEventListener("change", func);
}

void QGRadioButton::setChecked(bool checked) {
    _iqradioButton->setChecked(checked);
}

void QGRadioButton::setSelected(bool selected) {
    _iqradioButton->setChecked(selected);
}

void QGRadioButton::setText(const std::string& text) {
    _iqradioButton->setText(QString::fromStdString(text));
}

QButtonGroup* QGRadioButton::getButtonGroup(const std::string& group) {
    if (!_buttonGroups.containsKey(group)) {
        _buttonGroups.put(group, new QButtonGroup());
    }
    return _buttonGroups[group];
}

#endif // SPL_QT_GUI