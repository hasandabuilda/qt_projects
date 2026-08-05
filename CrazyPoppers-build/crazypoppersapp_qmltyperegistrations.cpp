/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<boardmodel.h>)
#  include <boardmodel.h>
#endif
#if __has_include(<bulletmodel.h>)
#  include <bulletmodel.h>
#endif
#if __has_include(<gameengine.h>)
#  include <gameengine.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_CrazyPoppers()
{
    qmlRegisterModule("CrazyPoppers", 254, 0);
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<BoardModel>("CrazyPoppers", 254);
    qmlRegisterTypesAndRevisions<BulletModel>("CrazyPoppers", 254);
    qmlRegisterTypesAndRevisions<GameEngine>("CrazyPoppers", 254);
    qmlRegisterEnum<GameEngine::Phase>("GameEngine::Phase");
    QMetaType::fromType<QAbstractItemModel *>().id();
    qmlRegisterEnum<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");
    qmlRegisterEnum<QAbstractItemModel::CheckIndexOption>("QAbstractItemModel::CheckIndexOption");
    QMetaType::fromType<QAbstractListModel *>().id();
    QT_WARNING_POP
    qmlRegisterModule("CrazyPoppers", 254, 254);
}

static const QQmlModuleRegistration crazyPoppersRegistration("CrazyPoppers", qml_register_types_CrazyPoppers);
