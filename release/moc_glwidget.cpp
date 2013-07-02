/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created: Fri Sep 25 21:47:21 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../glwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x05,
      29,   10,    9,    9, 0x05,
      42,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   55,    9,    9, 0x0a,
      83,   75,    9,    9, 0x0a,
     103,   75,    9,    9, 0x0a,
     125,  119,    9,    9, 0x0a,
     144,   10,    9,    9, 0x0a,
     164,   10,    9,    9, 0x0a,
     184,   10,    9,    9, 0x0a,
     204,   75,    9,    9, 0x0a,
     221,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLWidget[] = {
    "GLWidget\0\0value\0rotateX(int)\0rotateY(int)\0"
    "rotateZ(int)\0face\0showFaces(int)\0"
    "bEnable\0showWireFrame(bool)\0showTetra(bool)\0"
    "space\0setTetraSpace(int)\0xSliderChanged(int)\0"
    "ySliderChanged(int)\0zSliderChanged(int)\0"
    "enableSpin(bool)\0spincube()\0"
};

const QMetaObject GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWidget,
      qt_meta_data_GLWidget, 0 }
};

const QMetaObject *GLWidget::metaObject() const
{
    return &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget))
        return static_cast<void*>(const_cast< GLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: rotateX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: rotateY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: rotateZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: showFaces((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: showWireFrame((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: showTetra((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: setTetraSpace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: xSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: ySliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: zSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: enableSpin((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: spincube(); break;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void GLWidget::rotateX(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GLWidget::rotateY(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLWidget::rotateZ(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
