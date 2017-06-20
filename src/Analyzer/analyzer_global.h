#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(ANALYZER_LIB)
#  define ANALYZER_EXPORT Q_DECL_EXPORT
# else
#  define ANALYZER_EXPORT Q_DECL_IMPORT
# endif
#else
# define ANALYZER_EXPORT
#endif
