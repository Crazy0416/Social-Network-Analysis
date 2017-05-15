/****************************************************************************
** Meta object code from reading C++ file 'dblpanalysisapp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dblpanalysisapp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dblpanalysisapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dblpAnalysisApp_t {
    QByteArrayData data[7];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dblpAnalysisApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dblpAnalysisApp_t qt_meta_stringdata_dblpAnalysisApp = {
    {
QT_MOC_LITERAL(0, 0, 15), // "dblpAnalysisApp"
QT_MOC_LITERAL(1, 16, 18), // "Main_SlotVisualize"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 9), // "Main_TopK"
QT_MOC_LITERAL(4, 46, 14), // "Main_TopKfromA"
QT_MOC_LITERAL(5, 61, 10), // "Main_Chain"
QT_MOC_LITERAL(6, 72, 19) // "Main_AuthorCrawling"

    },
    "dblpAnalysisApp\0Main_SlotVisualize\0\0"
    "Main_TopK\0Main_TopKfromA\0Main_Chain\0"
    "Main_AuthorCrawling"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dblpAnalysisApp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void dblpAnalysisApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        dblpAnalysisApp *_t = static_cast<dblpAnalysisApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Main_SlotVisualize(); break;
        case 1: _t->Main_TopK(); break;
        case 2: _t->Main_TopKfromA(); break;
        case 3: _t->Main_Chain(); break;
        case 4: _t->Main_AuthorCrawling(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject dblpAnalysisApp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_dblpAnalysisApp.data,
      qt_meta_data_dblpAnalysisApp,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *dblpAnalysisApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dblpAnalysisApp::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_dblpAnalysisApp.stringdata0))
        return static_cast<void*>(const_cast< dblpAnalysisApp*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int dblpAnalysisApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
