/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[26];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "setFluidity"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 2), // "_f"
QT_MOC_LITERAL(4, 27, 13), // "setPlasticity"
QT_MOC_LITERAL(5, 41, 2), // "_p"
QT_MOC_LITERAL(6, 44, 13), // "setElasticity"
QT_MOC_LITERAL(7, 58, 2), // "_e"
QT_MOC_LITERAL(8, 61, 10), // "setDensity"
QT_MOC_LITERAL(9, 72, 2), // "_d"
QT_MOC_LITERAL(10, 75, 11), // "setPressure"
QT_MOC_LITERAL(11, 87, 12), // "scaleGravity"
QT_MOC_LITERAL(12, 100, 2), // "_g"
QT_MOC_LITERAL(13, 103, 20), // "setInteractionRadius"
QT_MOC_LITERAL(14, 124, 2), // "_i"
QT_MOC_LITERAL(15, 127, 15), // "toggleViscosity"
QT_MOC_LITERAL(16, 143, 2), // "_v"
QT_MOC_LITERAL(17, 146, 13), // "toggleSprings"
QT_MOC_LITERAL(18, 160, 2), // "_s"
QT_MOC_LITERAL(19, 163, 16), // "toggleRelaxation"
QT_MOC_LITERAL(20, 180, 2), // "_r"
QT_MOC_LITERAL(21, 183, 14), // "stopSimulation"
QT_MOC_LITERAL(22, 198, 17), // "setParticleNumber"
QT_MOC_LITERAL(23, 216, 9), // "setSpread"
QT_MOC_LITERAL(24, 226, 11), // "setVelocity"
QT_MOC_LITERAL(25, 238, 8) // "generate"

    },
    "MainWindow\0setFluidity\0\0_f\0setPlasticity\0"
    "_p\0setElasticity\0_e\0setDensity\0_d\0"
    "setPressure\0scaleGravity\0_g\0"
    "setInteractionRadius\0_i\0toggleViscosity\0"
    "_v\0toggleSprings\0_s\0toggleRelaxation\0"
    "_r\0stopSimulation\0setParticleNumber\0"
    "setSpread\0setVelocity\0generate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x08 /* Private */,
       4,    1,   92,    2, 0x08 /* Private */,
       6,    1,   95,    2, 0x08 /* Private */,
       8,    1,   98,    2, 0x08 /* Private */,
      10,    1,  101,    2, 0x08 /* Private */,
      11,    1,  104,    2, 0x08 /* Private */,
      13,    1,  107,    2, 0x08 /* Private */,
      15,    1,  110,    2, 0x08 /* Private */,
      17,    1,  113,    2, 0x08 /* Private */,
      19,    1,  116,    2, 0x08 /* Private */,
      21,    1,  119,    2, 0x08 /* Private */,
      22,    1,  122,    2, 0x08 /* Private */,
      23,    1,  125,    2, 0x08 /* Private */,
      24,    1,  128,    2, 0x08 /* Private */,
      25,    1,  131,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,   12,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   12,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setFluidity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setPlasticity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->setElasticity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->setDensity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->setPressure((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->scaleGravity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->setInteractionRadius((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->toggleViscosity((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->toggleSprings((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->toggleRelaxation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->stopSimulation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->setParticleNumber((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setSpread((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->setVelocity((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->generate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
