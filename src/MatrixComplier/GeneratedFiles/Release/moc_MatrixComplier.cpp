/****************************************************************************
** Meta object code from reading C++ file 'MatrixComplier.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MatrixComplier.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MatrixComplier.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MatrixComplier_t {
    QByteArrayData data[18];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MatrixComplier_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MatrixComplier_t qt_meta_stringdata_MatrixComplier = {
    {
QT_MOC_LITERAL(0, 0, 14), // "MatrixComplier"
QT_MOC_LITERAL(1, 15, 15), // "FileInfoDisplay"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 25), // "StaticContentDisplayAtEnd"
QT_MOC_LITERAL(4, 58, 7), // "content"
QT_MOC_LITERAL(5, 66, 22), // "StaticContentDisplayAt"
QT_MOC_LITERAL(6, 89, 3), // "pos"
QT_MOC_LITERAL(7, 93, 21), // "StaticContentDeleteAt"
QT_MOC_LITERAL(8, 115, 3), // "len"
QT_MOC_LITERAL(9, 119, 25), // "StaticContentDeleteBefore"
QT_MOC_LITERAL(10, 145, 9), // "LogInsert"
QT_MOC_LITERAL(11, 155, 9), // "VarInsert"
QT_MOC_LITERAL(12, 165, 4), // "name"
QT_MOC_LITERAL(13, 170, 9), // "VarDelete"
QT_MOC_LITERAL(14, 180, 20), // "LogInstructionRecall"
QT_MOC_LITERAL(15, 201, 5), // "index"
QT_MOC_LITERAL(16, 207, 18), // "InstructionProcess"
QT_MOC_LITERAL(17, 226, 11) // "instruction"

    },
    "MatrixComplier\0FileInfoDisplay\0\0"
    "StaticContentDisplayAtEnd\0content\0"
    "StaticContentDisplayAt\0pos\0"
    "StaticContentDeleteAt\0len\0"
    "StaticContentDeleteBefore\0LogInsert\0"
    "VarInsert\0name\0VarDelete\0LogInstructionRecall\0"
    "index\0InstructionProcess\0instruction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MatrixComplier[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x08 /* Private */,
       3,    1,   67,    2, 0x08 /* Private */,
       5,    2,   70,    2, 0x08 /* Private */,
       7,    2,   75,    2, 0x08 /* Private */,
       9,    2,   80,    2, 0x08 /* Private */,
      10,    1,   85,    2, 0x08 /* Private */,
      11,    2,   88,    2, 0x08 /* Private */,
      13,    1,   93,    2, 0x08 /* Private */,
      14,    1,   96,    2, 0x08 /* Private */,
      16,    1,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    6,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    8,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,    4,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QModelIndex,   15,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void MatrixComplier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MatrixComplier *_t = static_cast<MatrixComplier *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->FileInfoDisplay((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->StaticContentDisplayAtEnd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->StaticContentDisplayAt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->StaticContentDeleteAt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->StaticContentDeleteBefore((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->LogInsert((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->VarInsert((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->VarDelete((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->LogInstructionRecall((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 9: _t->InstructionProcess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MatrixComplier::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MatrixComplier.data,
      qt_meta_data_MatrixComplier,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MatrixComplier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MatrixComplier::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MatrixComplier.stringdata0))
        return static_cast<void*>(const_cast< MatrixComplier*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MatrixComplier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
