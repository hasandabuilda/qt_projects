/****************************************************************************
** Meta object code from reading C++ file 'gameengine.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../CrazyPoppers/src/gameengine.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameengine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10GameEngineE_t {};
} // unnamed namespace

template <> constexpr inline auto GameEngine::qt_create_metaobjectdata<qt_meta_tag_ZN10GameEngineE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "GameEngine",
        "QML.Element",
        "auto",
        "phaseChanged",
        "",
        "levelChanged",
        "tapsChanged",
        "scoreChanged",
        "comboChanged",
        "pausedChanged",
        "highestUnlockedLevelChanged",
        "popped",
        "row",
        "column",
        "tier",
        "startLevel",
        "index",
        "restartLevel",
        "nextLevel",
        "tap",
        "bestScore",
        "levelIndex",
        "levelNameAt",
        "tapBudgetAt",
        "board",
        "BoardModel*",
        "bullets",
        "BulletModel*",
        "phase",
        "Phase",
        "levelCount",
        "levelName",
        "tapBudget",
        "tapsRemaining",
        "tapsUsed",
        "score",
        "combo",
        "paused",
        "highestUnlockedLevel",
        "Idle",
        "Resolving",
        "Won",
        "Lost"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'phaseChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'levelChanged'
        QtMocHelpers::SignalData<void()>(5, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'tapsChanged'
        QtMocHelpers::SignalData<void()>(6, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'scoreChanged'
        QtMocHelpers::SignalData<void()>(7, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'comboChanged'
        QtMocHelpers::SignalData<void()>(8, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'pausedChanged'
        QtMocHelpers::SignalData<void()>(9, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'highestUnlockedLevelChanged'
        QtMocHelpers::SignalData<void()>(10, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'popped'
        QtMocHelpers::SignalData<void(int, int, int)>(11, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 }, { QMetaType::Int, 13 }, { QMetaType::Int, 14 },
        }}),
        // Method 'startLevel'
        QtMocHelpers::MethodData<void(int)>(15, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 16 },
        }}),
        // Method 'restartLevel'
        QtMocHelpers::MethodData<void()>(17, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'nextLevel'
        QtMocHelpers::MethodData<void()>(18, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'tap'
        QtMocHelpers::MethodData<void(int, int)>(19, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 }, { QMetaType::Int, 13 },
        }}),
        // Method 'bestScore'
        QtMocHelpers::MethodData<int(int) const>(20, 4, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::Int, 21 },
        }}),
        // Method 'levelNameAt'
        QtMocHelpers::MethodData<QString(int) const>(22, 4, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Int, 16 },
        }}),
        // Method 'tapBudgetAt'
        QtMocHelpers::MethodData<int(int) const>(23, 4, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::Int, 16 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'board'
        QtMocHelpers::PropertyData<BoardModel*>(24, 0x80000000 | 25, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'bullets'
        QtMocHelpers::PropertyData<BulletModel*>(26, 0x80000000 | 27, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'phase'
        QtMocHelpers::PropertyData<enum Phase>(28, 0x80000000 | 29, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'levelIndex'
        QtMocHelpers::PropertyData<int>(21, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'levelCount'
        QtMocHelpers::PropertyData<int>(30, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'levelName'
        QtMocHelpers::PropertyData<QString>(31, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'tapBudget'
        QtMocHelpers::PropertyData<int>(32, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'tapsRemaining'
        QtMocHelpers::PropertyData<int>(33, QMetaType::Int, QMC::DefaultPropertyFlags, 2),
        // property 'tapsUsed'
        QtMocHelpers::PropertyData<int>(34, QMetaType::Int, QMC::DefaultPropertyFlags, 2),
        // property 'score'
        QtMocHelpers::PropertyData<int>(35, QMetaType::Int, QMC::DefaultPropertyFlags, 3),
        // property 'combo'
        QtMocHelpers::PropertyData<int>(36, QMetaType::Int, QMC::DefaultPropertyFlags, 4),
        // property 'paused'
        QtMocHelpers::PropertyData<bool>(37, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'highestUnlockedLevel'
        QtMocHelpers::PropertyData<int>(38, QMetaType::Int, QMC::DefaultPropertyFlags, 6),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Phase'
        QtMocHelpers::EnumData<enum Phase>(29, 29, QMC::EnumFlags{}).add({
            {   39, Phase::Idle },
            {   40, Phase::Resolving },
            {   41, Phase::Won },
            {   42, Phase::Lost },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<GameEngine, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject GameEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10GameEngineE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10GameEngineE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10GameEngineE_t>.metaTypes,
    nullptr
} };

void GameEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<GameEngine *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->phaseChanged(); break;
        case 1: _t->levelChanged(); break;
        case 2: _t->tapsChanged(); break;
        case 3: _t->scoreChanged(); break;
        case 4: _t->comboChanged(); break;
        case 5: _t->pausedChanged(); break;
        case 6: _t->highestUnlockedLevelChanged(); break;
        case 7: _t->popped((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 8: _t->startLevel((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->restartLevel(); break;
        case 10: _t->nextLevel(); break;
        case 11: _t->tap((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 12: { int _r = _t->bestScore((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 13: { QString _r = _t->levelNameAt((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 14: { int _r = _t->tapBudgetAt((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (GameEngine::*)()>(_a, &GameEngine::phaseChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameEngine::*)()>(_a, &GameEngine::levelChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameEngine::*)()>(_a, &GameEngine::tapsChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameEngine::*)()>(_a, &GameEngine::scoreChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameEngine::*)()>(_a, &GameEngine::comboChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameEngine::*)()>(_a, &GameEngine::pausedChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameEngine::*)()>(_a, &GameEngine::highestUnlockedLevelChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameEngine::*)(int , int , int )>(_a, &GameEngine::popped, 7))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BoardModel* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BulletModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<BoardModel**>(_v) = _t->board(); break;
        case 1: *reinterpret_cast<BulletModel**>(_v) = _t->bullets(); break;
        case 2: *reinterpret_cast<enum Phase*>(_v) = _t->phase(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->levelIndex(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->levelCount(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->levelName(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->tapBudget(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->tapsRemaining(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->tapsUsed(); break;
        case 9: *reinterpret_cast<int*>(_v) = _t->score(); break;
        case 10: *reinterpret_cast<int*>(_v) = _t->combo(); break;
        case 11: *reinterpret_cast<bool*>(_v) = _t->isPaused(); break;
        case 12: *reinterpret_cast<int*>(_v) = _t->highestUnlockedLevel(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 11: _t->setPaused(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *GameEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10GameEngineE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void GameEngine::phaseChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GameEngine::levelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GameEngine::tapsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GameEngine::scoreChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GameEngine::comboChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void GameEngine::pausedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void GameEngine::highestUnlockedLevelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void GameEngine::popped(int _t1, int _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2, _t3);
}
QT_WARNING_POP
