#ifndef LOGMODEL_GLOBAL_H
#define LOGMODEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LOG_MODEL_LIBRARY)
#  define LOGMODEL_EXPORT Q_DECL_EXPORT
#else
#  define LOGMODEL_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGMODEL_GLOBAL_H
