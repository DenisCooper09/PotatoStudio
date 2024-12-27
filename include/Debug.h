#ifndef POTATO_STUDIO_DEBUG_H
#define POTATO_STUDIO_DEBUG_H

#if defined(PS_DEBUG_BUILD)
#   include <cstdio>
#   define PS_INFO(format, ...) fprintf(stdout, "[INFO] %s:%s\t| " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#   define PS_ERROR(format, ...) fprintf(stderr, "[ERROR] %s:%i\t| " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#elif defined(PS_RELEASE_BUILD)
#   define PS_INFO(format, ...)
#   define PS_ERROR(format, ...)
#else
#   error "Unknown build type."
#endif

#endif // POTATO_STUDIO_DEBUG_H
