/****************************************************************************
** Meta object code from reading C++ file 'qtcreate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qtcreate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtcreate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtCreate_t {
    QByteArrayData data[18];
    char stringdata[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtCreate_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtCreate_t qt_meta_stringdata_QtCreate = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QtCreate"
QT_MOC_LITERAL(1, 9, 12), // "EDFBtn_Click"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "RMSBtn_Click"
QT_MOC_LITERAL(4, 36, 12), // "DMSBtn_Click"
QT_MOC_LITERAL(5, 49, 12), // "LSTBtn_Click"
QT_MOC_LITERAL(6, 62, 13), // "MFPSBtn_Click"
QT_MOC_LITERAL(7, 76, 15), // "ClearOutputFile"
QT_MOC_LITERAL(8, 92, 15), // "ClearGanttGraph"
QT_MOC_LITERAL(9, 108, 8), // "LoadFile"
QT_MOC_LITERAL(10, 117, 8), // "SaveFile"
QT_MOC_LITERAL(11, 126, 17), // "LoadPartitionFile"
QT_MOC_LITERAL(12, 144, 12), // "LoadTaskFile"
QT_MOC_LITERAL(13, 157, 21), // "MFPSLoadPartitionFile"
QT_MOC_LITERAL(14, 179, 16), // "MFPSLoadTaskFile"
QT_MOC_LITERAL(15, 196, 10), // "LoadAction"
QT_MOC_LITERAL(16, 207, 8), // "SetTimes"
QT_MOC_LITERAL(17, 216, 10) // "SaveAction"

    },
    "QtCreate\0EDFBtn_Click\0\0RMSBtn_Click\0"
    "DMSBtn_Click\0LSTBtn_Click\0MFPSBtn_Click\0"
    "ClearOutputFile\0ClearGanttGraph\0"
    "LoadFile\0SaveFile\0LoadPartitionFile\0"
    "LoadTaskFile\0MFPSLoadPartitionFile\0"
    "MFPSLoadTaskFile\0LoadAction\0SetTimes\0"
    "SaveAction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtCreate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x09 /* Protected */,
      10,    0,  102,    2, 0x09 /* Protected */,
      11,    0,  103,    2, 0x09 /* Protected */,
      12,    0,  104,    2, 0x09 /* Protected */,
      13,    0,  105,    2, 0x09 /* Protected */,
      14,    0,  106,    2, 0x09 /* Protected */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtCreate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtCreate *_t = static_cast<QtCreate *>(_o);
        switch (_id) {
        case 0: _t->EDFBtn_Click(); break;
        case 1: _t->RMSBtn_Click(); break;
        case 2: _t->DMSBtn_Click(); break;
        case 3: _t->LSTBtn_Click(); break;
        case 4: _t->MFPSBtn_Click(); break;
        case 5: _t->ClearOutputFile(); break;
        case 6: _t->ClearGanttGraph(); break;
        case 7: _t->LoadFile(); break;
        case 8: _t->SaveFile(); break;
        case 9: { int _r = _t->LoadPartitionFile();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { int _r = _t->LoadTaskFile();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->MFPSLoadPartitionFile();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: { int _r = _t->MFPSLoadTaskFile();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 13: _t->LoadAction(); break;
        case 14: _t->SetTimes(); break;
        case 15: _t->SaveAction(); break;
        default: ;
        }
    }
}

const QMetaObject QtCreate::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QtCreate.data,
      qt_meta_data_QtCreate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QtCreate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtCreate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QtCreate.stringdata))
        return static_cast<void*>(const_cast< QtCreate*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QtCreate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
