/*
 * File: gscrollpane.h
 * -------------------
 *
 * @author Marty Stepp
 * @version 2018/09/01
 * - initial version
 */

#ifndef _gscrollpane_h
#define _gscrollpane_h

#include <QScrollArea>
#include <QWidget>
#include "ginteractor.h"

// forward declaration
class _Internal_QScrollArea;

/*
 * ...
 */
class GScrollPane : public GInteractor {
public:
    GScrollPane(GInteractor* interactor = nullptr, QWidget* parent = nullptr);
    virtual ~GScrollPane();
    virtual GInteractor* getInteractor() const;
    virtual _Internal_QWidget* getInternalWidget() const Q_DECL_OVERRIDE;
    virtual std::string getType() const Q_DECL_OVERRIDE;
    virtual QWidget* getWidget() const Q_DECL_OVERRIDE;
    virtual void setInteractor(GInteractor* interactor);
    virtual void setInteractorStretch(bool stretch);

private:
    Q_DISABLE_COPY(GScrollPane)

    _Internal_QScrollArea* _iqscrollarea;
    GInteractor* _interactor;

    friend class _Internal_QScrollArea;
};

// Internal class; not to be used by clients.
class _Internal_QScrollArea : public QScrollArea, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QScrollArea(GScrollPane* gscrollpane, QWidget* parent = nullptr);
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;

private:
    GScrollPane* _gscrollpane;
};

#include "private/init.h"   // ensure that Stanford C++ lib is initialized

#endif // _gscrollpane_h